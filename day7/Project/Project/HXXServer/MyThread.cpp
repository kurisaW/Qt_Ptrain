#include "MyThread.h"

#include <QDebug>
#include "MsgBuilder.h"
#include <QMutex>
#include "UserDao.h"

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
            isRead = false;
            //读取到的json串应该放在任务队列
            mutex.lock();
            tasks.push(jsonStr);
            mutex.unlock();
        }

        if(!tasks.empty())  //如果任务队列中有任务，那么处理任务
        {
            mutex.lock();
            QString jsonStr = tasks.front();    //获得队首的元素
            tasks.pop();;//出队，从队列中删除任务
            mutex.unlock();
            switch(MsgBuilder::getType(jsonStr))
            {
            case MsgBuilder::userRegister:
                deelUserRegisterMsg(jsonStr);
                break;
            case MsgBuilder::userLogin:
                deelUserLoginMsg(jsonStr);//用户登录
                deelUserLoginMsg(jsonStr);
                break;
            case MsgBuilder::userLoginSuc://用户登录成功
                deelUserLoginSucMsg(jsonStr);
                break;
            }
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

void MyThread::addUserLoginSucMsg(vector<UserData> v)
{
    QString jsonStr = MsgBuilder::buildUserLoginSucMsg(v);
    mutex.lock();
    tasks.push(jsonStr);
    mutex.unlock();
}

void MyThread::deelUserRegisterMsg(QString jsonStr)
{
    //1 获得用户的nickname passwd headid
    UserData userData;
    MsgBuilder::parseUserRegisterMsg(jsonStr, userData);
    //2 将这些数据插到数据库
    UserEntity e(userData.userId, userData.nickName, userData.passwd, userData.headId);
    UserDao::getInstance()->insertUser(e);
    //3 将自动生成的userid返回给客户端
    userData.userId = e.userId; //将数据库自动生成的账号赋值给userData
    QString jsonRet = MsgBuilder::buildUserRegisterReturnMsg(userData);
    socket->write(jsonRet.toLocal8Bit().data(),jsonRet.size());
}

void MyThread::deelUserLoginMsg(QString jsonStr)
{
    //1 获得用户的账号和密码
    UserData userData;
    MsgBuilder::parseUserLoginMsg(jsonStr, userData);

    //2 在数据库中查找账号和密码，看是否查找成功
    UserEntity e(userData.userId, userData.nickName, userData.passwd, userData.headId);
    bool login;
    UserDao::getInstance()->checkUser(e, login);
    userData.nickName = e.nickName;
    userData.headId = e.headId;

    //3 根据结果，构建成功或失败的json串
    QString jsonRet;
    if(login)
    {
        //登录成功，通知主线程有用户登录成功，用自定义信号通知主线程
        emit SigUserLoginSuc(userData, this);
    }
    else
    {
        //登录失败，直接返回失败信息
        jsonRet = MsgBuilder::buildUserLoginLoseMsg();
        //4 将json发送客户端
        QByteArray bdata = jsonRet.toLocal8Bit();
        socket->write(bdata.data(), bdata.size());
    }
}

void MyThread::deelUserLoginSucMsg(QString jsonStr)
{
    QByteArray bdata = jsonStr.toLocal8Bit();
    socket->write(bdata.data(),bdata.size());
}
