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
    MyThread(qintptr socketDescriptor,QObject* parent = 0);

    void run();
private slots:
    void onDisconnected();
    void onReadyRead();

signals:
    void SigUserLoginSuc(UserData, MyThread*);

public:     //在线程中以add开头都是主线程调用
    void addUserLoginSucMsg(vector<UserData> v);//主线程调用的函数，表示用户登录成功

private:    //以deel开头，都是子线程自己调用
    void deelUserRegisterMsg(QString jsonStr);  //处理用户注册
    void deelUserLoginMsg(QString jsonStr);     //处理用户登录
    void deelUserLoginSucMsg(QString jsonStr);  //处理用户登录成功
private:
    qintptr socketDescriptor;
    bool isRun;
    bool isRead;
    queue<QString> tasks;   //任务队列，每个任务都是一个json串
    QMutex mutex;   //互斥锁，所有使用任务队列的方法都要用到互斥锁
    QTcpSocket* socket;
};

#endif // MYTHREAD_H
