#include "RegisterDialog.h"
#include "ui_RegisterDialog.h"
#include "MsgBuilder.h"
#include <QMessageBox>
#include "MsgBuilder.h"
#include "UserSocket.h"

RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    connect(UserSocket::getInstance(),SIGNAL(readyRead()),this,SLOT(onReadyRead()));
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::closeEvent(QCloseEvent *e)
{
    disconnect(UserSocket::getInstance(),SIGNAL(readyRead()),this,SLOT(onReadyRead()));
}

void RegisterDialog::on_pushButton_register_clicked()
{
    QString nickname = ui->lineEdit_nickname->text();
    QString passwd = ui->lineEdit_passwd->text();
    QString nota = ui->lineEdit_nota->text();
    if(nickname.isEmpty() || passwd.isEmpty() || nota.isEmpty())
    {
        //弹出消息框提示
        QMessageBox::information(this, "错误", "昵称和密码不能为空");
        return;
    }

    if(passwd != nota)
    {
        //弹出消息框提示
        QMessageBox::information(this, "错误", "两次密码不一致");
        return;
    }

    UserData data;
    data.headId = 0;//假的头像id
    data.nickName = nickname;
    data.passwd = passwd;
    QString jsonStr = MsgBuilder::buildUserRegisterMsg(data);
    QByteArray bdata = jsonStr.toLocal8Bit();
    UserSocket::getInstance()->write(bdata.data(),bdata.size());
}

void RegisterDialog::onReadyRead()
{
    QByteArray bdata = UserSocket::getInstance()->readAll();
    QString jsonStr = QString::fromLocal8Bit(bdata);

    if(MsgBuilder::getType(jsonStr) == MsgBuilder::userRegisterReturn)
    {
        UserData userData;
        MsgBuilder::parseUserRegisterReturnMsg(jsonStr,userData);
        ui->label_userid->setText(userData.userId);
    }
}



