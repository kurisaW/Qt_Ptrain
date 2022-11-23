#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include "queue"
#include"QMutex"
#include "MyThread.h"
#include "MsgBuilder.h"
#include "vector"

using namespace std;

class MyThread : public QThread
{
    Q_OBJECT
public:
    //qintptr socketDescriptor参数需要传给线程，因为在线程中要通过这个参数创建QTcpSocket
    MyThread(qintptr socketDescriptor, QObject* parent = 0);

    
    void run();
    
public slots:
    void disconnected();
    void readyRead();

signals:
    void siguserLoginSuc(UserData,MyThread*);//用户登录成功的信号
    void sigUserOffline(UserData data);//用户下线

public:
    void addUserLoginSucMsg(vector<UserData> v);
    void addUserOnlineMsg(UserData data);//主线程通知子线程用户上线
    void addUserOfflineMsg(UserData data);//主线程通知子线程用户下线

private:
    void deelUserRegisterMsg(QString jsonStr);
    void deelUserLoginMsg(QString jsonStr);
    void deelUserLoginSucMsg(QString jsonStr);
    void deelUserOnlineMsg(QString jsonStr);//处理用户上线
    void deelUserOfflineMsg(QString jsonStr);//处理用户下线

private:
    qintptr socketDescriptor;
    bool isRun;
    bool isRead;
    queue<QString> tasks;
    QMutex mutex;
    QTcpSocket* socket;
    UserData userData;//当前线程的用户信息
};

#endif // MYTHREAD_H
