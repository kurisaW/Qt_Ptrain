#ifndef FRIENDWINDOW_H
#define FRIENDWINDOW_H

#include <QMainWindow>
#include <vector>
#include "MsgBuilder.h"
#include <QListWidgetItem>
#include <map>
#include "ChatDialog.h"

using namespace std;

namespace Ui {
class FriendWindow;
}

class FriendWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit FriendWindow(vector<UserData> users, QWidget *parent = 0);
    ~FriendWindow();
    
private slots:
    void onReadyRead();
    void onChatDialogClose(UserData userData);
    //双击好友
    void on_listWidget_friend_itemDoubleClicked(QListWidgetItem *item);
    
private:
    void initFriendList(vector<UserData> users);//初始化好友列表
    void addWaitMsgToUserItem(UserData from, QString msg);//向UserItem中添加未读消息
    
    void deelUserOnline(QString jsonStr);//好友上线
    void deelUserOffline(QString jsonStr);//好友下线
    void deelUserReceiveMsg(QString jsonStr);//收到消息
private:
    Ui::FriendWindow *ui;
    map<UserData, ChatDialog*> dialogs;//用于管理已经打开过的聊天窗口，每个好友对应一个聊天窗口
};

#endif // FRIENDWINDOW_H
