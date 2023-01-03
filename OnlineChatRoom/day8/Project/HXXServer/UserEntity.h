#ifndef USERENITY_H
#define USERENITY_H
#include<QString>

struct UserEntity
{
    QString userId;
    QString nickName;
    QString passwd;
    int headId;
    UserEntity(QString userId,QString nickName,QString passwd,int headId=0);
};

#endif // USERENITY_H
