#include "UserDao.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

UserDao* UserDao::instance = 0;

UserDao::UserDao()
{
    //在构造函数打开数据库
    //如果每次执行数据库的操作，都创建一个UserDao对象，会使得打开和关闭数据库的操作很频繁，不利于程序运行
    //所以将UserDao封装成单例模式
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("hxx");
    db.setDatabaseName("hxx.db");
    db.open();
    
    QSqlQuery query;
    //exec函数  execute 执行sql语句
    query.exec("create table if not exists user(\
                      userid integer primary key autoincrement,\
                      password char(20),\
                      nickname char(20),\
                      headid integer\
                      )");
    //在注册用户时，我们会将用户的密码、昵称、头像插入数据库，然后自动生成userid作为用户账号。然后再把userid读取返回给客户端。
    query.exec("insert into user values(100000,'abc123','admin',0)");//先插入一个原始用户，目的是为了给userid一个起始值，这样注册的第一个用户的userid就是100001
}

UserDao::UserDao(const UserDao &other)
{
    
}

UserDao::~UserDao()
{
    //在析构函数关闭数据库
    db.close();
}

bool UserDao::insertUser(UserEntity &e)
{
    QSqlQuery query;
    //当sql语句中需要一些参数时，不能直接执行exec。
    //prepare是格式化sql语句用的，其中的?表示需要格式化的数据
    query.prepare("insert into user(password, nickname, headid) values(?,?,?)");
    query.bindValue(0, e.passwd);//0代表第一个?，使用e.password替换sql语句中的第一个问号
    query.bindValue(1, e.nickName);
    query.bindValue(2, e.headId);
    bool ok1 = query.exec();//把值绑定好之后就可以执行sql语句
    
    bool ok2 = query.exec("SELECT LAST_INSERT_ROWID()");//查询插入的最后一条数据的id，就是刚刚注册的账号
    if(query.next())
    {
        //将查询到的新用户的userid，赋值给形参
        e.userId = query.record().value(0).toString();//value(0)因为我们不是按照字段查找，0代表record对象中的第一个数据
    }
    return ok1 && ok2;//ok1和ok2都是真就返回真，否则返回假
}

bool UserDao::checkUser(UserEntity &e, bool &suc)
{
    QSqlQuery query;
    query.prepare("select * from user where userid = ? and password = ?");
    query.bindValue(0, e.userId);
    query.bindValue(1, e.passwd);
    bool ok = query.exec();

    if(suc = query.next())//if中既要给suc赋值，又要判断suc的值
    {
        //登录成功读取用户的数据
        e.nickName = query.record().value("nickname").toString();
        e.headId = query.record().value("headid").toInt();
    }
    return ok;
}

UserDao *UserDao::getInstance()
{
    if(instance == 0)
        instance = new UserDao;
    return instance;
}

void UserDao::releaseInstance()
{
    if(instance == 0)
        return;
    delete instance;
    instance = 0;
}

