#include "UserItem.h"
#include "ui_UserItem.h"

UserItem::UserItem(UserData userData,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserItem),
    userData(userData)
{
    ui->setupUi(this);
    QString info = QString("%1(%2)").arg(userData.nickName).arg(userData.userId);
    ui->label_name->setText(info);
}

UserItem::~UserItem()
{
    delete ui;
}
