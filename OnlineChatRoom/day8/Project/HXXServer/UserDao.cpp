#include "UserDao.h"
#include<QSQlQuery>
#include<QSqlRecord>
#include<QVariant>
UserDao*UserDao::instance=0;
UserDao::UserDao()
{
    //在构造函数打开数据库
        db=QSqlDatabase::addDatabase("QSQLITE");
        db.setHostName("hxx");
        db.setDatabaseName("hxx.db");
        db.open();
        QSqlQuery query;//QSqlQuery对象必须在打开数据库之后创建，所以QSqlQuery对象一般都定义成局部对象
           query.exec("create table if not exists user(\
                      userid integer primary key autoincrement,\
                      password char(20),\
                      nickname char(20),\
                      headid integer\
                      )");
           query.exec("insert into user values(100000,'abc123','admin',0)");
}

UserDao::~UserDao()
{
db.close();
}

bool UserDao::insertUser(UserEntity &e)
{
    QSqlQuery query;
        query.prepare("insert into user(nickname, password, headid) values(?,?,?)");
        query.bindValue(0, e.nickName);
        query.bindValue(1, e.passwd);
        query.bindValue(2, e.headId);
        bool ok1=query.exec();
        bool ok2= query.exec("SELECT LAST_INSERT_ROWID()");//查询插入的最后一条数据的id，就是刚刚注册的账号
         if(query.next())
         {
            e.userId= query.record().value(0).toString();//value(0)因为我们不是按照字段查找，0代表record对象中的第一个数据
         }
         return ok1&&ok2;

}

bool UserDao::checkUser(UserEntity &e, bool &suc)
{

    QSqlQuery query;
    query.prepare("select * from user where userid = ? and password = ?");
    query.bindValue(0, e.userId);
    query.bindValue(1, e.passwd);
    bool ok =query.exec();
    /*bool exist = false;
    //如果账号密码查询失败，则不会有结果，所以下面的循环不会执行，所以循环下面exist值是false
    while(query.next())
    {
        e.nickname = query.record().value("nickname").toString();
        exist = true;
    }
    cout<<exist;*/
    if(suc=query.next())
    {
    e.nickName=query.record().value("nickname").toString();
    e.headId= query.record().value("headid").toInt();
    }
    return ok;

}

UserDao *UserDao::getInstance()
{
    if(instance==0)
        instance=new UserDao;
    return instance;
}

void UserDao::releaseInstance()
{
    if(instance==0)
        return;
    delete instance;
    instance=0;
}
UserDao::UserDao(const UserDao &other)
{

}
