#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "MsgBuilder.h"
#include "UserDao.h"
#include <QHostAddress>

#include <QDebug>

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

    //因为newConnection信号发送时QTcpServer已经在主线程中创建了
    connect(server, SIGNAL(newConnectionForThread(qintptr)),this,SLOT(onNewConnection(qintptr)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onNewConnection(qintptr socketDesc)
{
    //收到连接，创建线程，根据socketDesc创建socket对象
    MyThread* thread = new MyThread(socketDesc,this);

    //当线程的run函数执行完毕，会发送出finish信号，我们要让线程收到finish()信号后删除线程对象
    connect(thread,SIGNAL(finished()),thread,SLOT(deleteLater()));
    connect(thread,SIGNAL(SigUserLoginSuc(UserData , MyThread*)),this,SLOT(onUserLoginSuc(UserData , MyThread*)));
    thread->start();
}

void MainWindow::onUserLoginSuc(UserData userData, MyThread *thread)
{
    //将登录用户以外的用户传给登录用户
    vector<UserData> v;
    for(map<UserData, MyThread*>::iterator iter = users.begin();
        iter != users.end(); iter++)
    {
        v.push_back(iter->first);
    }
    thread->addUserLoginSucMsg(v);//将数据发送给客户端
    //将登录用户加入到user中
    users.insert(pair<UserData, MyThread*>(userData,thread));
}
