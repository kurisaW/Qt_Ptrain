#ifndef USERDAO_H
#define USERDAO_H
#include"UserEntity.h"
#include<QSqlDatabase>

class UserDao
{
public:

    bool insertUser(UserEntity &e);//插入数据用于注册注册成功之后生成userId写在形参对象中
    bool checkUser(UserEntity &e,bool& suc);//用于用户登录参数2表示登录是否成功
    static UserDao*getInstance();
    static void releaseInstance();
private:
    UserDao();
    UserDao(const UserDao& other);
    ~UserDao();
    QSqlDatabase db;
    static UserDao *instance;
};

#endif // USERDAO_H
