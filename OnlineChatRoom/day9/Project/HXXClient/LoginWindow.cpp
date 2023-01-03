#include "LoginWindow.h"
#include "ui_LoginWindow.h"
#include "RegisterDialog.h"//包含头文件的目的是为了声明
//""在指定路径中查找头文件   <>在库中查找
#include "UserSocket.h"
#include <QHostAddress>
#include <QMessageBox>
#include "MsgBuilder.h"
#include <QDebug>
#include "FriendWindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_register, SIGNAL(clicked()), this, SLOT(onRegisterPushButtonClicked()));
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::onRegisterPushButtonClicked()
{
    //运行注册界面之前，先断开登录界面的readyRead信号。避免两个界面都能受到readyRead信号，产生数据的冲突
    disconnect(UserSocket::getInstance(), SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    
    RegisterDialog* rd = new RegisterDialog(this);
    //显示窗口有两种方式
    //1.普通显示
    //rd->show();
    //2.模态显示
    rd->exec();//程序会阻塞，等界面关闭，才继续执行，使用模态显示，必须指定父节点.
    
    //从注册界面返回登录界面后，再次连接登录界面的readyRead信号
    connect(UserSocket::getInstance(), SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

void LoginWindow::on_pushButton_connect_clicked()
{
    QString ip = ui->lineEdit_ip->text();
    UserSocket::getInstance()->connectToHost(QHostAddress(ip), 12345);
    connect(UserSocket::getInstance(), SIGNAL(connected()), this, SLOT(onConnected()));
    connect(UserSocket::getInstance(), SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

void LoginWindow::on_pushButton_login_clicked()
{
    /*
        1.获得用户输入的用户名和密码
        2.创建UserData对象，将用户名和密码赋值到UserData对象的成员中
        3.使用MsgBuilder构建json串
        4.使用UserSocket发送json串
    */
    QString userId = ui->lineEdit_userid->text();
    QString passwd = ui->lineEdit_passwd->text();
    if(userId.isEmpty() || passwd.isEmpty())
    {
        QMessageBox::information(this, "错误", "账号和密码不能为空");
        return;
    }
    
    UserData userData;
    userData.userId = userId;
    userData.passwd = passwd;
    
    QString jsonStr = MsgBuilder::buildUserLoginMsg(userData);
    
    QByteArray bdata = jsonStr.toLocal8Bit();
    UserSocket::getInstance()->write(bdata.data(), bdata.size());
}

void LoginWindow::onConnected()
{
    QMessageBox::information(this, "恭喜", "连接服务器成功");
}

void LoginWindow::onReadyRead()
{
    QByteArray bdata = UserSocket::getInstance()->readAll();
    QString jsonStr = QString::fromLocal8Bit(bdata);
    switch(MsgBuilder::getType(jsonStr))
    {
    case MsgBuilder::userLoginSuc:
        deelLoginSuc(jsonStr);
        break;
    case MsgBuilder::userLoginLose:
        QMessageBox::information(this, "登录信息", "登录失败");
        break;
    }
}

void LoginWindow::deelLoginSuc(QString jsonStr)
{
    vector<UserData> users;
    UserData userData;
    MsgBuilder::parseUserLoginSucMsg(jsonStr, userData, users);
    UserSocket::getInstance()->setUserData(userData);//保存当前用户信息
    
    FriendWindow* fw = new FriendWindow(users);
    fw->show();
    close();//关闭登陆界面
    //断开信号与槽
    disconnect(UserSocket::getInstance(), SIGNAL(readyRead()), 
               this, SLOT(onReadyRead()));
}
