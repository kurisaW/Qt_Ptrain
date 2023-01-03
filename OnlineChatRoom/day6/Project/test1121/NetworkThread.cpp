#include "NetworkThread.h"
#include <QDebug>
#include <QMutex>

extern int source;
extern QMutex mutex;

NetWorkThread::NetWorkThread(QObject* parent):QThread(parent)
{
    
}



void NetWorkThread::run()
{
    for(int i = 0;i < 100000;i++)
    {
        mutex.lock();
        source--;
        mutex.unlock();
    }
}


