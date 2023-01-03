#include "UserEntity.h"

//初始化列表，()外面都是成员，()里面都是形参
UserEntity::UserEntity(QString userId, QString nickName, QString passwd, int headId):
    userId(userId),nickName(nickName),passwd(passwd),headId(headId)
{

}

