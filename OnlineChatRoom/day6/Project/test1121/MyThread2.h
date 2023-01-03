#ifndef MYTHREAD2_H
#define MYTHREAD2_H

#include <QThread>
#include "UserData.h"

class MyThread2 : public QThread
{
    Q_OBJECT
public:
    MyThread2(QObject* parent = 0);
    void run();

signals://定义信号的关键字，因为信号不是函数，不可以调用，所以没有访问权限

    void threadValue(UserData val);
};

#endif // MYTHREAD2_H
