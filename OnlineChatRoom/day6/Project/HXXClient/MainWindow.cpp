#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "RegisterDialog.h" //包含头文件目的是为了声明
#include <QHostAddress>
#include "UserSocket.h"
#include "QMessagebox"
#include <QDebug>
#include <QString>

#include "ui_RegisterDialog.h"
#include "MsgBuilder.h"
#include "UserSocket.h"

//11.16
#include <QHostInfo>
#include <QHostAddress>
//



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_register,SIGNAL(clicked()),this,SLOT(onRegisterButtonClicked()));

    //11.16
//    QString localHostName = QHostInfo::localHostName();//获得本地主机的名字
//    QHostInfo info = QHostInfo::fromName(localHostName);//根据主机名字获得主机信息
//    //QList是QT给我们提供的链表
//    //一般情况下，封装好的数据结构都是模板
//    /*
//    模板有什么用？
//    用类型作为参数，避免重复的逻辑。模板又被称为静态多态。
//    所以QList<QHostAddress>链表中存放的数据类型是QHostAddress类型。
//    */
//    QList<QHostAddress> list = info.addresses();//获得主机中所有的地址ipv4和ipv6
//    //遍历链表，但是我这个遍历方式不好！遍历链表应该使用迭代器。但是这个遍历方式好理解。
//    for(int i = 0;i < list.size();i++)
//    {
//        //list[i]获得链表中的i元素，就是QHostAddress对象，并判断地址的协议类型
//        //打印ipv4协议的地址
//        if(list[i].protocol()==QAbstractSocket::IPv4Protocol)
//            qDebug()<<list[i].toString();
//    }
    //

    //11.17:1
//    server = new QTcpServer(this);
//    server->listen(QHostAddress::Any,12345);
//    connect(server,SIGNAL(newConnection()),this,SLOT(onNewConnection()));
    //


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onRegisterButtonClicked()
{
    //运行注册界面之前，先断开登陆界面的readtRead信号，避免产生数据冲突
    disconnect(UserSocket::getInstance(),SIGNAL(readyRead()),this,SLOT(onReadyRead()));

    // new+类型名：表示在堆空间中创建一个该类型的对象，返回一个指向该对象的指针。堆空间的对象没有名字
    //this指向调用成员函数的对象，在这里this指向的是MainWindows对象
    RegisterDialog* rd = new RegisterDialog(this);
    //显示窗口
    //1、普通显示
//    rd->show();
    //2、模态显示
    rd->exec();//程序会阻塞，等界面关闭，才继续执行,使用模态显示必须指定父节点

    //从注册界面返回登陆界面，再次连接登陆界面的readyRead信号
    connect(UserSocket::getInstance(),SIGNAL(readyRead()),this,SLOT(onReadyRead()));
}

void MainWindow::on_pushButton_connect_clicked()
{
    QString ip = ui->lineEdit_ip->text();
    UserSocket::getInstance()->connectToHost(QHostAddress(ip),12345);
    connect(UserSocket::getInstance(),SIGNAL(connected()),this,SLOT(onConnected()));
    connect(UserSocket::getInstance(),SIGNAL(readyRead()),this,SLOT(onReadyRead()));
}


void MainWindow::on_pushButton_login_clicked()
{
    /*
    1、获得用户输入的用户名和密码
    2、创建UserData对象，将用户名和密码赋值到UserData对象
    3、使用MsgBuilder构建json串
    4、使用UserSocket发送json串
    */

    QString userID = ui->lineEdit_id->text();
    QString passwd = ui->lineEdit_Passwd->text();
    if(userID.isEmpty() || passwd.isEmpty())
    {
        QMessageBox::information(this,"错误","账号和密码不一致");
        return;
    }

    UserData userData;
    userData.userId = userID;
    userData.passwd = passwd;

    QString jsonStr = MsgBuilder::buildUserLoginMsg(userData);
    QByteArray bdata = jsonStr.toLocal8Bit();
    UserSocket::getInstance()->write(bdata.data(),bdata.size());

}

void MainWindow::onConnected()
{
    qDebug()<<"4444444444444444";
    QMessageBox::information(this,"ok","successful!");
}

void MainWindow::onReadyRead()
{
    QByteArray bdata = UserSocket::getInstance()->readAll();
    QString jsonStr = QString::fromLocal8Bit(bdata);
    switch(MsgBuilder::getType(jsonStr))
    {
        case MsgBuilder::userLoginSuc:
            QMessageBox::information(this,"登录信息", "登录成功");
            break;
         case MsgBuilder::userLoginLose:
            QMessageBox::information(this,"登录信息","登陆失败");
            break;
    }
}

//11.17:1
//void MainWindow::onNewConnection()
//{
//    QTcpSocket* client;
//    client = server->nextPendingConnection();//获得与客户端通信用的QTcpsocket对象
//    connect(client, SIGNAL(disconnected()),this,SLOT(onDisConnection()));
//    connect(client, SIGNAL(readyRead()),this,SLOT(onReadyRead()));
//}

//void MainWindow::onDisConnection()
//{
//    ui->label_info->setText("断开连接");
//}

//void MainWindow::onReadyRead()
//{
//    QByteArray bdata2 = client->readAll();
//    QString data = QString::fromLocal8Bit(bdata2);
//    ui->label_info->setText(data);
//}

//


