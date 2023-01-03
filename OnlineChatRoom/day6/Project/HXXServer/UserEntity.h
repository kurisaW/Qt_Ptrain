#ifndef USERENTITY_H
#define USERENTITY_H

#include <QString>

/*
对User表中的各个字段的数据进行封装
*/


struct UserEntity
{
    QString userId;
    QString nickName;
    QString passwd;
    int headId;


    //为了方便对对象的初始化，我们需要一个构造函数
    UserEntity(QString userId, QString nickName, QString passwd, int headId = 0);
};

#endif // USERENTITY_H
