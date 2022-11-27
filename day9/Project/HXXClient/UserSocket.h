#ifndef USERSOCKET_H
#define USERSOCKET_H

#include <QTcpSocket>
#include "MsgBuilder.h"

/*
UserSocket是单例模式，继承自QTcpSocket，我们在客户端的项目中要使用
UserSocket对象进行tcp通信。
UserSocket还要保存当前登录用户的信息。
*/
class UserSocket : public QTcpSocket
{
    Q_OBJECT//派生自QObject的类，都要在私有权限中调用Q_OBJECT宏
private:
    UserSocket();
    ~UserSocket();
    UserSocket(const UserSocket& other);
    static UserSocket* instance;
    UserData userData;//登录用户的信息
public:
    static UserSocket* getInstance();
    static void releaseInstance();//释放对象
    //内联函数，建议编译器在编译时将内联函数在调用处展开，省去调用函数的开销，提高执行效率。
    //内联函数要求函数很小，否则编译器会拒绝内联。
    inline void setUserData(UserData data)
    {
        userData = data;
    }
    inline UserData getUserData() const
    {
        return userData;
    }
};

#endif // USERSOCKET_H
