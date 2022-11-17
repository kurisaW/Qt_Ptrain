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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_register,SIGNAL(clicked()),this,SLOT(onRegisterButtonClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onRegisterButtonClicked()
{
    // new+类型名：表示在堆空间中创建一个该类型的对象，返回一个指向该对象的指针。堆空间的对象没有名字
    //this指向调用成员函数的对象，在这里this指向的是MainWindows对象
    RegisterDialog* rd = new RegisterDialog(this);
    //显示窗口
    //1、普通显示
    rd->show();
    //2、模态显示
//    rd->exec();//程序会阻塞，等界面关闭，才继续执行,使用模态显示必须指定父节点
}

void MainWindow::on_pushButton_connect_clicked()
{
    QString ip = ui->lineEdit_ip->text();
    qDebug()<<"11111111111111   "<<ip;
    UserSocket::getInstance()->connectToHost(QHostAddress(ip),12345);
    qDebug()<<"222222222222222222";
    connect(UserSocket::getInstance(),SIGNAL(connected()),this,SLOT(onConnected()));
    qDebug()<<"33333333333333333333";
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
