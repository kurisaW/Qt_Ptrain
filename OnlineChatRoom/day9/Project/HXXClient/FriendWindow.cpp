#include "FriendWindow.h"
#include "ui_FriendWindow.h"
#include "UserItem.h"
#include "UserSocket.h"

/*
基本的封装原则
当一个函数太大了，它一定可以拆分成若干个函数。
当一个类太大了，它一定可以拆分成若干个类。
我们要避免过于臃肿的类和函数。
*/
//随着项目代码越写越多，可能会有一些功能上不健全的地方，或者一些小bug，我们先不去处理这些不尽如人意的地方。
FriendWindow::FriendWindow(vector<UserData> users, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FriendWindow)
{
    ui->setupUi(this);
    initFriendList(users);
    connect(UserSocket::getInstance(), SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    UserData userData = UserSocket::getInstance()->getUserData();
    QString info = QString("%1(%2)").arg(userData.nickName).arg(userData.userId);
    setWindowTitle(info);
}

FriendWindow::~FriendWindow()
{
    delete ui;
}

void FriendWindow::onReadyRead()
{
    QByteArray bdata = UserSocket::getInstance()->readAll();
    QString jsonStr = QString::fromLocal8Bit(bdata);
    switch(MsgBuilder::getType(jsonStr))
    {
    case MsgBuilder::userOnline:
        deelUserOnline(jsonStr);
        break;
    case MsgBuilder::userOffline:
        deelUserOffline(jsonStr);
        break;
    case MsgBuilder::userReceiveMsg:
        deelUserReceiveMsg(jsonStr);
        break;
    }
}

void FriendWindow::onChatDialogClose(UserData userData)
{
    delete dialogs[userData];//删除窗口对象
    dialogs.erase(userData);//从map中删除键值对
}

void FriendWindow::initFriendList(vector<UserData> users)
{
    for(int i = 0;i < users.size();i++)
    {
        UserItem* userItem = new UserItem(users[i], ui->listWidget_friend);
        QListWidgetItem* item = new QListWidgetItem(ui->listWidget_friend);
        item->setSizeHint(userItem->size());
        ui->listWidget_friend->setItemWidget(item, userItem);
    }
}

void FriendWindow::addWaitMsgToUserItem(UserData from, QString msg)
{
    for(int i = 0;i < ui->listWidget_friend->count();i++)
    {
        QListWidgetItem* item = ui->listWidget_friend->item(i);
        QWidget* widget = ui->listWidget_friend->itemWidget(item);
        UserItem* userItem = dynamic_cast<UserItem*>(widget);
        //找到要删除的好友
        if(userItem->getUserData().userId == from.userId)
        {
            userItem->addWaitMsg(msg);
        }
    }
}

void FriendWindow::deelUserOnline(QString jsonStr)
{
    //获得好友数据
    UserData userData;
    MsgBuilder::parseUserOnlineMsg(jsonStr, userData);
    //将数据添加到控件中
    UserItem* userItem = new UserItem(userData, ui->listWidget_friend);
    QListWidgetItem* item = new QListWidgetItem(ui->listWidget_friend);
    item->setSizeHint(userItem->size());
    ui->listWidget_friend->setItemWidget(item, userItem);
}

void FriendWindow::deelUserOffline(QString jsonStr)
{
    UserData userData;
    MsgBuilder::parseUserOnlineMsg(jsonStr, userData);
    
    for(int i = 0;i < ui->listWidget_friend->count();i++)
    {
        //整个循环是在QListWidget中查找好友目标，循环中的API操作不需要在意
        QListWidgetItem* item = ui->listWidget_friend->item(i);
        QWidget* widget = ui->listWidget_friend->itemWidget(item);
        UserItem* userItem = dynamic_cast<UserItem*>(widget);
        //找到要删除的好友
        if(userItem->getUserData().userId == userData.userId)
        {
            ui->listWidget_friend->takeItem(i);//从QLiistWidget中删除好友
            delete userItem;//删除控件对象
        }
    }
}

void FriendWindow::deelUserReceiveMsg(QString jsonStr)
{
    UserData from, to;
    QString msg;
    MsgBuilder::parseUserReceiveMsg(jsonStr, from, to, msg);

    if(dialogs.count(from) == 0)//如果没有打开对方的聊天窗口，则不添加信息
    {
        addWaitMsgToUserItem(from, msg);
        return;
    }
    
    dialogs[from]->addMsg(msg);
}

void FriendWindow::on_listWidget_friend_itemDoubleClicked(QListWidgetItem *item)
{
    QWidget* widget = ui->listWidget_friend->itemWidget(item);
    UserItem* userItem = dynamic_cast<UserItem*>(widget);
    //如果这个好友的聊天窗口已经打开过了，则不再打开
    if(dialogs.count(userItem->getUserData()) > 0)
    {
        return;
    }
    
    //创建聊天窗口，同时传入好友的信息
    ChatDialog* cd = new ChatDialog(userItem->getUserData(), this);
    cd->show();
    
    connect(cd, SIGNAL(sigChatDialogClose(UserData)), 
            this, SLOT(onChatDialogClose(UserData)));
    //显示未读信息
    QStringList waitMsg = userItem->getWaitMsg();
    for(int i = 0;i < waitMsg.size();i++)
    {
        cd->addMsg(waitMsg[i]);
    }
    userItem->clearWaitMsg();
    
    
    //将窗口和好友以键值对形式放在dialogs中管理
    dialogs.insert(pair<UserData, ChatDialog*>(userItem->getUserData(), cd));
}
