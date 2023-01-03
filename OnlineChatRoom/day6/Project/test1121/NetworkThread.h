#ifndef NETWORKTHREAD_H
#define NETWORKTHREAD_H

#include <QThread>
using namespace std;

class NetWorkThread : public QThread
{
    Q_OBJECT
public:
    NetWorkThread(QObject* parent = 0);
  
    void run();//重写run函数，是线程要执行的逻辑
};

#endif // NETWORKTHREAD_H
