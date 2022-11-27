#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QTcpSocket>
//#include <QTcpServer>
#include <MyTcpServer.h>
#include "MyThread.h"
#include <map>
#include "MsgBuilder.h"
#include <vector>
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

private slots://槽函数
    void onNewConnection(qintptr socketDes);

    void onUserLoginSuc(UserData userData, MyThread* thread);
    void onUserOffline(UserData userData);
    void onUserSendMsg(UserData from, UserData to, QString msg);

private:
    Ui::MainWindow *ui;
    //QTcpServer *server;
    MyTcpServer *server;
    //QTcpSocket *client;
    map<UserData,MyThread*> users;
};


#endif // MAINWINDOW_H
