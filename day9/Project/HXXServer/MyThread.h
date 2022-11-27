#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <queue>
#include <QMutex>
#include "MsgBuilder.h"
#include <vector>

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
    void sigUserLoginSuc(UserData, MyThread*);//用户登录成功的信号
    void sigUserOffline(UserData);//用户下线
    void sigUserSendMsg(UserData from, UserData to, QString msg);//用户发送消息
    
public://在线程中，我的命名规则：以add开头都是主线程调用的函数
    void addUserLoginSucMsg(UserData userData, vector<UserData> v);//主线程调用的函数，用户登录成功
    void addUserOnlineMsg(UserData data);//主线程通知子线程用户上线
    void addUserOfflineMsg(UserData data);//主线程通知子线程用户下线
    void addUserReceiveMsg(UserData from, UserData to, QString msg);//主线程通知子线程用户发消息
    
private://在线程中，我的命名规则：以deel开头都是子线程自己调用的函数
    void deelUserRegisterMsg(QString jsonStr);//处理用户注册
    void deelUserLoginMsg(QString jsonStr);//处理用户登录
    void deelUserLoginSucMsg(QString jsonStr);//处理用户登录成功
    void deelUserOnlineMsg(QString jsonStr);//处理用户上线
    void deelUserOfflineMsg(QString jsonStr);//处理用户下线
    void deelUserSendMsg(QString jsonStr);//处理用户发送消息
    void deelUserReceiveMsg(QString jsonStr);//处理用户接收消息
private:
    qintptr socketDescriptor;
    bool isRun;
    bool isRead;
    queue<QString> tasks;//任务队列，每个任务都是一个json串
    QMutex mutex;//互斥锁，所有使用任务队列的地方都要使用互斥锁
    QTcpSocket* socket;
    UserData userData;//当前线程的用户信息
};

#endif // MYTHREAD_H
