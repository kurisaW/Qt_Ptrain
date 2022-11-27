#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QTcpServer>

class MyTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    MyTcpServer(QObject* parent = 0);
    
signals:
    void newConnectionForThread(qintptr socketDescriptor);
    
protected:
    void incomingConnection(qintptr socketDescriptor);
};

#endif // MYTCPSERVER_H
