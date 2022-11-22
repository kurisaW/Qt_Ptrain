#include "MyTcpServer.h"

MyTcpServer::MyTcpServer(QObject* parent):QTcpServer(parent)
{

}

void MyTcpServer::incomingConnection(qintptr socketDescriptor)
{
    //QT的QTcpserver在这个函数中创建了QTcpSocket对象，但是QTcoSocket对象只能在主线程中使用
    //所以我们不能在这里创建QTcpSocket对象，要把socketDescription参数发送给线程对象，在线程中创建QTcpSocket对象
    //应该通过信号的方式将socketDesciption
    emit newConnectionForThread(socketDescriptor);
}

