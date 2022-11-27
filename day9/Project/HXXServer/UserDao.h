#ifndef USERDAO_H
#define USERDAO_H

#include "UserEntity.h"
#include <QSqlDatabase>

/*
封装对user表的各种操作
*/

class UserDao
{
public:
    //所有操作的返回值都是bool类型，表示数据库操作是否成功
    /*
        插入数据，用于注册，注册成功后生成的userid写在形参对象中
    */
    bool insertUser(UserEntity& e);
    /*
        用于用户登录
        参数2：表示登录是否成功
    */
    bool checkUser(UserEntity& e, bool& suc);
    
    static UserDao* getInstance();
    static void releaseInstance();
private:
    UserDao();
    UserDao(const UserDao& other);
    ~UserDao();
    QSqlDatabase db;
    static UserDao *instance;
};

#endif // USERDAO_H
