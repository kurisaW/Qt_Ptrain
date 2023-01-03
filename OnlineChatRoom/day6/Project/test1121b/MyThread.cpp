#include "MyThread.h"

#include <QDebug>

MyThread::MyThread(qintptr socketDescriptor, QObject *parent):
    QThread(parent), socketDescriptor(socketDescriptor),isRun(true),isRead(false)
{

}

void MyThread::run()
{
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket,SIGNAL(disconnected()),this,SLOT(onDisconnected()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(onReadyRead()));

    //socket的连接断开，应该结束事件循环，事件循环结束run函数就结束了，线程就结束了
    //因为线程要和客户端匹配，客户端
    //线程中所有读写逻辑都写在事件循环中
    while(isRun)
    {
        if(isRead)
        {
            QByteArray bdata = socket->readAll();
            QString jsonStr = QString::fromLocal8Bit(bdata);
            qDebug()<<jsonStr;
            isRead = false;
        }
        socket->waitForReadyRead(10);//等待读取数据，这个函数必须出现
    }
    delete socket;
}

void MyThread::onDisconnected()
{
    isRun = false;
}

void MyThread::onReadyRead()
{
    isRead = true;
}
