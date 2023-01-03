#include "UserDao.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QSqlDatabase>
#include <QDebug>

UserDao* UserDao::instance = 0;

UserDao::UserDao()
{
    //在构造函数打开数据库
    //如果每次执行数据库的操作，都创建一个UserDao对象，会使得打开和关闭数据库的操作很频繁，不利于程序的运行
    //所以将UserDao封装成单例模式
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("hxx");
    db.setDatabaseName("hxx.db");
    db.open();

    QSqlQuery query;//QSqlQuery对象必须在打开数据库之后创建，所以QSqlQuery对象一般都定义成局部对象

    query.exec("create table if not exists user(\
               userId integer primary key autoincrement,\
               password char(20),\
               nickName char(20),\
               headId integer\
               )");
    query.exec("insert into user values(100000,'abc123','admin',0)");

}

UserDao::~UserDao()
{
    //在析构函数关闭数据库
    db.close();
}

bool UserDao::insertUser(UserEntity &e)
{
    QSqlQuery query;
    query.prepare("insert into user(nickname, password, headid) values(?,?,?)");
    query.bindValue(0, e.nickName);
    query.bindValue(1, e.passwd);
    query.bindValue(2, e.headId);
    bool ok1 = query.exec();
    bool ok2 = query.exec("SELECT LAST_INSERT_ROWID()");//查询插入的最后一条数据的id，就是刚刚注册的账号

    if(query.next())
    {
        e.userId = query.record().value(0).toString();//value(0)因为我们不是按照字段查找，0代表record对象中的第一个数据
    }
    return ok1 && ok2;
}

bool UserDao::checkUser(UserEntity &e, bool &suc)
{
    QSqlQuery query;
    query.prepare("select * from user where userid = ? and password = ?");
    query.bindValue(0, e.userId);
    query.bindValue(1, e.passwd);

    bool ok = query.exec();

    if(suc = query.next())
    {
        //登录成功读取用户数据
        e.nickName = query.record().value("nickname").toString();
        e.headId = query.record().value("headid").toInt();
    }
    return ok;
}

UserDao::UserDao(const UserDao &other)
{

}

UserDao *UserDao::getInstance()
{
    if(instance == 0)
        instance =new UserDao;
    return instance;
}

void UserDao::releaseInstance()
{
    if(instance == 0)
        return;
    delete instance;
    instance = 0;
}
