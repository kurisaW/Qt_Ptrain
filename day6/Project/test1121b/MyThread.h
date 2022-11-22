#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QTcpSocket>

class MyThread : public QThread
{
    Q_OBJECT
public:
    MyThread(qintptr socketDescriptor,QObject* parent = 0);

    void run();
private slots:
    void onDisconnected();
    void onReadyRead();

private:
    qintptr socketDescriptor;
    QTcpSocket* socket;
    bool isRun;
    bool isRead;
};

#endif // MYTHREAD_H
