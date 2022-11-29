#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QTcpServer>//换成MyTcpServer
#include "MyTcpServer.h"
#include <QTcpSocket>
#include "MyThread.h"
#include <map>
#include <vector>
#include "MsgBuilder.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void onNewConnection(qintptr socketDesc);//server的槽函数 客户端新的连接

    void onUserLoginSuc(UserData userData, MyThread* thread);//用户登录成功
    void onUserOffline(UserData userData);//用户下线
    void onUserSendMsg(UserData from, UserData to, QString msg);//用户发送消息
private:
    Ui::MainWindow *ui;
    MyTcpServer* server;
    map<UserData, MyThread*> users;//保存用户的线程，每当有一个用户登录成功，users中插入一对数据
};

#endif // MAINWINDOW_H
