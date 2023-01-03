#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QTcpServer>     //换成MyTcpServer.h
#include "MyTcpServer.h"
#include <QTcpSocket>
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

private slots:
    void onNewConnection(qintptr socketDesc);//客户端新的连接

    void onUserLoginSuc(UserData userData, MyThread* thread);

private:
    Ui::MainWindow *ui;
//    QTcpServer* server;   //换成MyTcpServer
    MyTcpServer* server;

//    QTcpSocket* client;   //不再需要有一个用户登录
    map<UserData, MyThread*> users;//保存用户的线程,每当有一个用户成功登录，users中插入一段数据
};

#endif // MAINWINDOW_H
