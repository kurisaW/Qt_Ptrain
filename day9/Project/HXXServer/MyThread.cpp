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
            //读取到的json串应该放在任务队列中
            mutex.lock();
            tasks.push(jsonStr);
            mutex.unlock();
        }
        
        if(!tasks.empty())//如果任务队列中有任务，那么处理任务
        {
            mutex.lock();
            QString jsonStr = tasks.front();//获得队首的元素
            tasks.pop();//出队，从队列中删除任务
            mutex.unlock();
            switch(MsgBuilder::getType(jsonStr))
            {
            case MsgBuilder::userRegister:
                deelUserRegisterMsg(jsonStr);
                break;
            case MsgBuilder::userLogin://用户登录
                deelUserLoginMsg(jsonStr);
                break;
            case MsgBuilder::userLoginSuc://用户登录成功
                deelUserLoginSucMsg(jsonStr);
                break;
            case MsgBuilder::userOnline:
                deelUserOnlineMsg(jsonStr);//用户上线
                break;
            case MsgBuilder::userOffline://用户下线
                deelUserOfflineMsg(jsonStr);
                break;
            case MsgBuilder::userSendMsg://用户发送消息
                deelUserSendMsg(jsonStr);
                break;
            case MsgBuilder::userReceiveMsg://用户接收消息
                deelUserReceiveMsg(jsonStr);
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
    qDebug()<<"dis";
}

void MyThread::readyRead()
{
    isRead = true;
    qDebug()<<"read";
}

void MyThread::addUserLoginSucMsg(UserData userData,vector<UserData> v)
{
    QString jsonStr = MsgBuilder::buildUserLoginSucMsg(userData, v);
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

void MyThread::addUserReceiveMsg(UserData from, UserData to, QString msg)
{
    QString jsonStr = MsgBuilder::buildUserReceiveMsg(from, to, msg);
    mutex.lock();
    tasks.push(jsonStr);
    mutex.unlock();
}

void MyThread::deelUserRegisterMsg(QString jsonStr)
{
    //1. 获得用户的 nickName  passwd  headid
    UserData userData;
    MsgBuilder::parseUserRegisterMsg(jsonStr, userData);
    //2. 将这些数据插入到数据库
    UserEntity e(userData.userId, userData.nickName, userData.passwd, userData.headId);
    UserDao::getInstance()->insertUser(e);
    //3. 将自动生产成的userid返回给客户端
    userData.userId = e.userId;//将数据库自动生成的账号赋值给userData
    QString jsonRet = MsgBuilder::buildUSerRegisterReturnMsg(userData);
    socket->write(jsonRet.toLocal8Bit().data(), jsonRet.toLocal8Bit().size()); 
}

void MyThread::deelUserLoginMsg(QString jsonStr)
{
    //1. 获得用户的账号和密码
    UserData userData;
    MsgBuilder::parseUserLoginMsg(jsonStr, userData);
    //2. 在数据库查找账号和密码，看是否查找成功
    UserEntity e(userData.userId, userData.nickName, userData.passwd, userData.headId);
    bool login;
    UserDao::getInstance()->checkUser(e, login);
    userData.nickName = e.nickName;
    userData.headId = e.headId;
    //3. 根据结果，构建成功或者失败的json串
    QString jsonRet;
    if(login)
    {
        //通知主线程，有用户登录成功了，用自定义信号通知主线程
        emit sigUserLoginSuc(userData, this);
        this->userData = userData;//保存登录用户的数据
    }
    else
    {
        //登录失败，直接返回失败信息
        jsonRet = MsgBuilder::buildUserLoginLoseMsg();
        //4. 将json串发给客户端
        QByteArray bdata = jsonRet.toLocal8Bit();
        socket->write(bdata.data(), bdata.size());
    }
    
}

void MyThread::deelUserLoginSucMsg(QString jsonStr)
{
    QByteArray bdata = jsonStr.toLocal8Bit();
    socket->write(bdata.data(), bdata.size());
}

void MyThread::deelUserOnlineMsg(QString jsonStr)
{
    QByteArray bdata = jsonStr.toLocal8Bit();
    socket->write(bdata.data(), bdata.size());
}

void MyThread::deelUserOfflineMsg(QString jsonStr)
{
    QByteArray bdata = jsonStr.toLocal8Bit();
    socket->write(bdata.data(), bdata.size());
}

void MyThread::deelUserSendMsg(QString jsonStr)
{
    UserData from, to;
    QString msg;
    MsgBuilder::parseUserSendMsg(jsonStr, from, to, msg);
    //在子线程中能不能完成消息转发?不能，需要发信号给主线程，主线程完成消息的转发
    emit sigUserSendMsg(from, to, msg);
}

void MyThread::deelUserReceiveMsg(QString jsonStr)
{
    QByteArray bdata = jsonStr.toLocal8Bit();
    socket->write(bdata.data(), bdata.size());
}

