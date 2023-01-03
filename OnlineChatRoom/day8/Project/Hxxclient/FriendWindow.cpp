#include "FriendWindow.h"
#include "ui_FriendWindow.h"
#include "UserItem.h"
#include "UserSocket.h"

FriendWindow::FriendWindow(vector<UserData> users,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FriendWindow)
{
    ui->setupUi(this);
    initFriendList(users);
    connect(UserSocket::getInstance(),SIGNAL(readyRead()),this,SLOT(onReadyRead()));
}

FriendWindow::~FriendWindow()
{
    delete ui;
}

void FriendWindow::initFriendList(vector<UserData> users)
{
    for(int i= 0;i<users.size();i++)
    {
        UserItem* userItem = new UserItem(users[i],ui->listWidget_friend);
        QListWidgetItem* item = new QListWidgetItem(ui->listWidget_friend);
        item->setSizeHint(userItem->size());
        ui->listWidget_friend->setItemWidget(item,userItem);
    }
}

void FriendWindow::deelUserOnline(QString jsonStr)
{
    //获得好友数据
    UserData userData;
    MsgBuilder::parseUserOnlineMsg(jsonStr,userData);

    //将数据添加到控件中
    UserItem* userItem = new UserItem(userData,ui->listWidget_friend);
    QListWidgetItem* item = new QListWidgetItem(ui->listWidget_friend);
    item->setSizeHint(userItem->size());
    ui->listWidget_friend->setItemWidget(item,userItem);
}


void FriendWindow::on_listWidget_friend_itemDoubleClicked(QListWidgetItem *item)
{
    QWidget* widget = ui->listWidget_friend->itemWidget(item);
    UserItem* useritem = dynamic_cast<UserItem*>(widget);
}

void FriendWindow::onReadyRead()
{
    QByteArray bdata = UserSocket::getInstance()->readAll();
    QString jsonStr = QString::fromLocal8Bit(bdata);
    switch(MsgBuilder::getType(jsonStr))
    {
    case MsgBuilder::userOnline:
        deelUserOnline(jsonStr);
        qDebug()<<"online: "<<jsonStr;
        break;
    case MsgBuilder::userOffline:
        qDebug()<<"offline: "<<jsonStr;
        break;
    }
}
