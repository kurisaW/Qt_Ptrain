#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "MsgBuilder.h"
#include "UserDao.h"
#include <QHostAddress>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //跨线程发送带有自定义数据的自定义信号，需要将自定义类型注册
    qRegisterMetaType<UserData>("UserData");
    qRegisterMetaType<MyThread*>("MyThread*");
    
    server = new MyTcpServer(this);
    server->listen(QHostAddress::Any, 12345);
    //信号换成newConnectionForThread，因为newConnection信号发送时QTcpServer已经在主线程中为我们创建了QTcpSocket
    connect(server, SIGNAL(newConnectionForThread(qintptr)), 
            this, SLOT(onNewConnection(qintptr)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onNewConnection(qintptr socketDesc)
{
    //收到连接，创建线程，线程中根据socketDesc创建socket对象
    MyThread* thread = new MyThread(socketDesc, this);
    //当线程的run函数执行完毕，会发出finished()信号，我们要让线程接收到finished()信号后删除线程对象
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread, SIGNAL(sigUserLoginSuc(UserData,MyThread*)), 
            this, SLOT(onUserLoginSuc(UserData,MyThread*)));
    connect(thread, SIGNAL(sigUserOffline(UserData)), 
            this, SLOT(onUserOffline(UserData)));
    connect(thread, SIGNAL(sigUserSendMsg(UserData,UserData,QString)), 
            this, SLOT(onUserSendMsg(UserData,UserData,QString)));
    thread->start();
}

void MainWindow::onUserLoginSuc(UserData userData, MyThread* thread)
{
    //将登录用户以外的其他用户传给登录用户
    vector<UserData> v;
    for(map<UserData, MyThread*>::iterator iter = users.begin();
        iter != users.end();iter++)
    {
        v.push_back(iter->first);
        //遍历所有在线用户，通知他们登录用户上线了
        iter->second->addUserOnlineMsg(userData);
    }
    thread->addUserLoginSucMsg(userData, v);//将数据发送给登陆客户端
    
    
    //将登录用户加入到user中
    users.insert(pair<UserData, MyThread*>(userData, thread));
}

void MainWindow::onUserOffline(UserData userData)
{
    //判断这个用户是否登录成功
    if(users.count(userData) == 0)//users中没有userData说明没有登录过
    {
        return;
    }
    users.erase(userData);//从登录用户中删除这个用户
    for(map<UserData, MyThread*>::iterator iter = users.begin();iter != users.end();
        iter++)
    {
        iter->second->addUserOfflineMsg(userData);
    }
}

void MainWindow::onUserSendMsg(UserData from, UserData to, QString msg)
{
    if(users.count(to) == 0)//接收消息的用户不在线就不转发
        return;
    //users[to]根据to这个键找到对应的值（既线程对象(MyThread)的指针）
    users[to]->addUserReceiveMsg(from, to, msg);
}


