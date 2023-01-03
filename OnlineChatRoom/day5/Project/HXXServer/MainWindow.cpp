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
    server = new QTcpServer(this);
    server->listen(QHostAddress::Any, 12345);
    connect(server, SIGNAL(newConnection()),this,SLOT(onNewConnection()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onNewConnection()
{
    client = server->nextPendingConnection();
    connect(client, SIGNAL(disconnected()),this,SLOT(onDisconnected()));
    connect(client, SIGNAL(readyRead()),this,SLOT(onReadyRead()));
}

void MainWindow::onDisconnected()
{

}

void MainWindow::onReadyRead()
{
    QByteArray bdata = client->readAll();
    QString jsonStr = QString::fromLocal8Bit(bdata);
    //判断json串的type  0 登录    1 注册
    switch(MsgBuilder::getType(jsonStr))
    {
        case MsgBuilder::userLogin:
            deelUserLogin(jsonStr);
            break;
        case MsgBuilder::userRegister:
            deelUserRegister(jsonStr);
            break;
    }

}

void MainWindow::deelUserRegister(QString jsonStr)
{
    //1 获得用户的nickname passwd headid
    UserData userData;
    MsgBuilder::parseUserRegisterMsg(jsonStr, userData);
    //2 将这些数据插到数据库
    UserEntity e(userData.userId, userData.nickName, userData.passwd, userData.headId);
    UserDao::getInstance()->insertUser(e);
    //3 将自动生成的userid返回给客户端
    userData.userId = e.userId;
    QString jsonRet = MsgBuilder::buildUserRegisterReturnMsg(userData);
    client->write(jsonRet.toLocal8Bit().data(),jsonRet.size());
}

void MainWindow::deelUserLogin(QString jsonStr)
{
    //1 获得用户的账号和密码
    UserData userData;
    MsgBuilder::parseUserLoginMsg(jsonStr, userData);

    //2 在数据库中查找账号和密码，看是否查找成功
    UserEntity e(userData.userId, userData.nickName, userData.passwd, userData.headId);
    bool login;
    UserDao::getInstance()->checkUser(e, login);

    //3 根据结果，构建成功或失败的json串
    QString jsonRet;
    if(login)
    {
        jsonRet = MsgBuilder::buildUserLoginSucMsg();
    }
    else
    {
        jsonRet = MsgBuilder::buildUserLoginLoseMsg();
    }

    //4 将json发送客户端
    QByteArray bdata = jsonRet.toLocal8Bit();
    client->write(bdata.data(), bdata.size());
}

