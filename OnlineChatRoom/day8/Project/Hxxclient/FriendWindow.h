#ifndef FRIENDWINDOW_H
#define FRIENDWINDOW_H

#include <QMainWindow>
#include <vector>
#include "MsgBuilder.h"
#include "QListWidget"

using namespace std;

namespace Ui {
class FriendWindow;
}

class FriendWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FriendWindow(vector<UserData> users,QWidget *parent = 0);
    ~FriendWindow();
private slots:
    void on_listWidget_friend_itemDoubleClicked(QListWidgetItem *item);//双击好友
    void onReadyRead();

private:
    void initFriendList(vector<UserData> users);//初始化好友列表

    void deelUserOnline(QString jsonStr);//好友上线

private:
    Ui::FriendWindow *ui;
};

#endif // FRIENDWINDOW_H
