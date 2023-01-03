#include "MyThread.h"
#include <QDebug>
#include <QMutex>

extern int source;//声明外部的变量，表明现在使用的全局变量是在其他文件中定义的。
extern QMutex mutex;

MyThread::MyThread(QObject* parent):
    QThread(parent)
{
    
}

void MyThread::run()
{
    for(int i = 0;i < 100000;i++)
    {
        mutex.lock();//在对资源写操作之前，上锁
        source++;
        mutex.unlock();//写操作之后解锁
    }
}


