#include "UserItem.h"
#include "ui_UserItem.h"

UserItem::UserItem(UserData userData, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserItem),
    userData(userData)
{
    ui->setupUi(this);
    QString info = QString("%1(%2)").arg(userData.nickName).arg(userData.userId);
    ui->label_name->setText(info);//显示用户的昵称和id
    //没有未读信息的时候隐藏
    ui->label_count->setVisible(false);
    ui->label_red->setVisible(false);
}

UserItem::~UserItem()
{
    delete ui;
}

void UserItem::addWaitMsg(QString msg)
{
    waitMsg.append(msg);
    //显示未读信息条数
    ui->label_count->setVisible(true);
    ui->label_red->setVisible(true);
    //最多显示99条
    int count = waitMsg.size();
    ui->label_count->setNum(count>99?99:count);
}

void UserItem::clearWaitMsg()
{
    waitMsg.clear();
    ui->label_count->setVisible(false);
    ui->label_red->setVisible(false);
}
