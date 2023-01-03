#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Msgbuilder.h"
#include "UserDao.h"
#include<QHostAddress>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qRegisterMetaType<UserData>("UserData");
    qRegisterMetaType<MyThread*>("MyThread*");
    server=new MyTcpServer(this);
    server->listen(QHostAddress::Any,12345);
    connect(server,SIGNAL(newConnectionForThread(qintptr)),this,SLOT(onNewConnection(qintptr)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onNewConnection(qintptr socketDes)
{
    MyThread* thread = new MyThread(socketDes,this);
    connect(thread,SIGNAL(finished()),thread,SLOT(deleteLater()));
    connect(thread,SIGNAL(siguserLoginSuc(UserData,MyThread*)),this,SLOT(onUserLoginSuc(UserData,MyThread*)));
    connect(thread,SIGNAL(sigUserOffline(UserData)),this,SLOT(onUserOffline(UserData)));

    thread->start();
}

void MainWindow::onUserLoginSuc(UserData userData, MyThread* thread)
{
    //将登录用户以外的其他用户传给登录用户
    vector<UserData> v;
    for(map<UserData,MyThread*>::iterator iter = users.begin();
        iter != users.end() ; iter++)
    {
        v.push_back(iter->first);
        //遍历所有在线用户，通知他们登录用户上线了
        iter->second->addUserOnlineMsg(userData);

    }
    thread->addUserLoginSucMsg(v);//将数据发给登录客户端

    users.insert(pair<UserData,MyThread*>(userData,thread));
}

void MainWindow::onUserOffline(UserData userData)
{
    //判断这个用户是否登录成功
    if(users.count(userData) == 0)//没有userdata，说明没有登录
    {
        return;
    }
    users.erase(userData);//从登录用户中删除这个用户
    for(map<UserData , MyThread*>::iterator iter = users.begin();
        iter != users.end(); iter++)
    {
        iter->second->addUserOfflineMsg(userData);
    }
}

