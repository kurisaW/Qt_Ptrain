#include "UserSocket.h"

UserSocket* UserSocket::instance = 0;
UserSocket::UserSocket() : QTcpSocket(0)
{

}

UserSocket::~UserSocket()
{

}

UserSocket::UserSocket(const UserSocket &other)
{

}

UserSocket *UserSocket::getInstance()
{
    if(instance == 0)
    {
        instance = new UserSocket;
    }
    return instance;
}

void UserSocket::releaseInstance()
{
    if(instance != 0)
    {
        delete instance;
    }
    instance = 0;//将释放对象后的指针赋值空指针，避免出现野指针
}





