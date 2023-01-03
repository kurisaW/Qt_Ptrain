#include "MyThread.h"
#include <QDebug>
#include "MsgBuilder.h"
#include "UserDao.h"
MyThread::MyThread(qintptr socketDescriptor, QObject* parent):
    QThread(parent), socketDescriptor(socketDescriptor), isRun(true), isRead(false)
{

}

void MyThread::run()
{
    //run是线程执行的逻辑，所以socket对象只能在run中创建
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    //socket的连接断开，应该结束事件循环，事件循环结束run函数就结束，线程就结束了
    //因为线程要和客户端匹配，客户端断开连接，线程就可以结束了
    //线程所有的读写逻辑都写在事件循环中
    while(isRun)
    {
        if(isRead)
        {
            QByteArray bdata = socket->readAll();
            QString jsonStr = QString::fromLocal8Bit(bdata);
            isRead = false;
            mutex.lock();
            tasks.push(jsonStr);
            mutex.unlock();
        }
        if(!tasks.empty())
        {
            mutex.lock();
            QString jsonStr = tasks.front();
            tasks.pop();
            mutex.unlock();
            switch(MsgBuilder::getType(jsonStr))
            {
            case MsgBuilder::userRegister:
                deelUserRegisterMsg(jsonStr);
                break;
            case MsgBuilder::userLogin:
                deelUserLoginMsg(jsonStr);
                break;
            case MsgBuilder::userLoginSuc:
                deelUserLoginSucMsg(jsonStr);
                break;
            case MsgBuilder::userOnline:
                deelUserOnlineMsg(jsonStr);
                break;
            case MsgBuilder::userOffline:
                deelUserOfflineMsg(jsonStr);
                break;
            }
        }
        socket->waitForReadyRead(10);//等待读取数据，等待10毫秒，等待时间可以灵活处理，但是这个函数必须出现在事件循环中
    }
    emit sigUserOffline(userData);//发送用户下线信号
    delete socket;
}

void MyThread::disconnected()
{
    isRun = false;
}

void MyThread::readyRead()
{
    isRead = true;
}

void MyThread::addUserLoginSucMsg(vector<UserData> v)
{
      QString jsonStr = MsgBuilder::buildUserLoginSucMsg(v);
      mutex.lock();
      tasks.push(jsonStr);
      mutex.unlock();
}

void MyThread::addUserOnlineMsg(UserData data)
{
    QString jsonStr = MsgBuilder::buildUserOnlineMsg(data);
    mutex.lock();
    tasks.push(jsonStr);
    mutex.unlock();
}

void MyThread::addUserOfflineMsg(UserData data)
{
    QString jsonStr = MsgBuilder::buildUserOfflineMsg(data);
    mutex.lock();
    tasks.push(jsonStr);
    mutex.unlock();
}

void MyThread::deelUserRegisterMsg(QString jsonStr)
{
        //获得用户的nickname passwd headid
        UserData userData;
        MsgBuilder::parseUserRegisterMsg(jsonStr,userData);
        //将数据插入到数据库
        UserEntity e(userData.userId,userData.nickName,userData.passwd,userData.headId);
        UserDao::getInstance()->insertUser(e);
        //将自动生成的userid返回给客户端
        userData.userId=e.userId;//将数据库自动生成的账号赋值给
        QString jsonRet=MsgBuilder::buildUserRegisterReturnMsg(userData);
        socket->write(jsonRet.toLocal8Bit().data(),jsonRet.toLocal8Bit().size());
}

void MyThread::deelUserLoginMsg(QString jsonStr)
{
        UserData userData;
        MsgBuilder::parseUserLoginMsg(jsonStr,userData);
        UserEntity e(userData.userId,userData.nickName,userData.passwd,userData.headId);
        bool login;
        UserDao::getInstance()->checkUser(e,login);
        userData.nickName=e.nickName;
        userData.headId= e.headId;
        QString jsonRet;
        if(login)
        {
            emit siguserLoginSuc(userData,this);
            this->userData = userData;//保存登录用户的数据
        }
        else
        {
            jsonRet = MsgBuilder::buildUserLoginLoginLose();
            QByteArray bdata = jsonRet.toLocal8Bit();
            socket->write(bdata.data(),bdata.size());
        }
}

void MyThread::deelUserLoginSucMsg(QString jsonStr)
{
    QByteArray bdata = jsonStr.toLocal8Bit();
    socket->write(bdata.data(),bdata.size());
}

void MyThread::deelUserOnlineMsg(QString jsonStr)
{
    QByteArray bdata = jsonStr.toLocal8Bit();
    socket->write(bdata.data(),bdata.size());
}

void MyThread::deelUserOfflineMsg(QString jsonStr)
{
    QByteArray bdata = jsonStr.toLocal8Bit();
    socket->write(bdata.data(),bdata.size());
}

