#include "LoginWindow.h"
#include "ui_LoginWindow.h"
#include "RegisterDialog.h"
#include "UserSocket.h"
#include <QHostAddress>

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_register,SIGNAL(clicked()),this,SLOT(onRegisterButtonClicked());
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::onRegisterButtonClicked()
{
    RegisterDialog* rd = new RegisterDialog(this);
    //显示窗口
    //1、普通显示
    rd->show();
    //2、模态显示
    rd->exec();//程序会阻塞，等界面关闭，才继续执行,使用模态显示必须指定父节点
}
