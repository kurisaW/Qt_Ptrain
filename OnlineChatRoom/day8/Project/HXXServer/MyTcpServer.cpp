#include "MyTcpServer.h"

MyTcpServer::MyTcpServer(QObject* parent):QTcpServer(parent)
{
    
}

void MyTcpServer::incomingConnection(qintptr socketDescriptor)
{
    //QT的QTcpServer在这个函数中创建了QTcpSocket对象，但是这个QTcpSocket对象只能在主线程使用
    //所以我们不能在这里创建QTcpSocket对象，要把这个socketDescriptor参数发给线程对象，在线程
    //中创建QTcpSocket对象。
    //应该通过信号的形式把socketDescriptor发送出去
    emit newConnectionForThread(socketDescriptor);
}

