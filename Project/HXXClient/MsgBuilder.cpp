#include "MsgBuilder.h"
#include "cjson/CJsonObject.hpp"
#include <string>//cjson支持c++string

using namespace neb;
using namespace std;

//注册json串
MsgBuilder::MsgType MsgBuilder::getType(QString jsonStr)
{
    CJsonObject obj(jsonStr.toStdString());
    int type;
    obj.Get(string("type"), type);
    return (MsgType)type;
}

QString MsgBuilder::buildUserRegisterMsg(UserData data)
{
    CJsonObject obj;
    obj.Add(string("type"),userRegister);//用于区分json串类型
    obj.Add(string("nickname"),data.nickName.toStdString());
    obj.Add(string("passwd"),data.passwd.toStdString());
    obj.Add(string("headid"),data.headId);
    QString jsonStr(obj.ToString().c_str());
    //c_str是string类的函数，将string类型转换成char*
    //QString的构造函数不支持string类型，支持char*
    return jsonStr;
}

void MsgBuilder::parseUserRegisterMsg(QString jsonStr, UserData& data)
{
    CJsonObject obj(jsonStr.toStdString());//将json字符串创建CJsonObject对象
    string nickName;
    obj.Get(string("nickname"),nickName);
    data.nickName = QString(nickName.c_str());
    string passwd;
    obj.Get(string("passwd"),passwd);
    data.passwd = QString(passwd.c_str());
    obj.Get(string("headid"),data.headId);
}

QString MsgBuilder::buildUserLoginMsg(UserData data)
{
    CJsonObject obj;
    obj.Add(string("type"),userLogin);//用于区分json串类型
    obj.Add(string("userid"),data.userId.toStdString());
    obj.Add(string("passwd"),data.passwd.toStdString());
    QString jsonStr(obj.ToString().c_str());
    //c_str是string类的函数，将string类型转换成char*
    //QString的构造函数不支持string类型，支持char*
    return jsonStr;
}

//登录json串
void MsgBuilder::parseUserLoginMsg(QString jsonStr, UserData &data)
{
    CJsonObject obj(jsonStr.toStdString());//将json字符串创建CJsonObject对象
    string userId;
    obj.Get(string("userid"),userId);
    string passwd;
    obj.Get(string("passwd"),passwd);


    data.passwd = QString(passwd.c_str());
    data.userId = QString(userId.c_str());

}

QString MsgBuilder::buildUserRegisterReturnMsg(UserData data)
{
    CJsonObject obj;
    obj.Add(string("type"),userRegisterReturn);//用于区分json串类型
    obj.Add(string("userid"),data.userId.toStdString());
    QString jsonStr(obj.ToString().c_str());
    //c_str是string类的函数，将string类型转换成char*
    //QString的构造函数不支持string类型，支持char*
    return jsonStr;
}

void MsgBuilder::parseUserRegisterReturnMsg(QString jsonStr, UserData &data)
{
    CJsonObject obj(jsonStr.toStdString());//将json字符串创建CJsonObject对象
    string userId;
    obj.Get(string("userid"),userId);

    data.userId = QString(userId.c_str());
}



QString MsgBuilder::buildUserLoginSucMsg(UserData userData ,vector<UserData> v)
{
    CJsonObject obj;
    obj.Add(string("type"),userLoginSuc);//jsonStr串的类型
    obj.Add(string("userid"),userData.userId.toStdString());
    obj.Add(string("headid"),userData.headId);
    obj.Add(string("nickname"),userData.nickName.toStdString());

    CJsonObject users;
    for(int i = 0;i<v.size();i++)
    {
        CJsonObject user;
        user.Add("userid",v[i].userId.toStdString());
        user.Add("nickname",v[i].nickName.toStdString());
        user.Add("headid",v[i].headId);
        users.Add(user);
    }
    obj.Add("users",users);

    QString jsonStr(obj.ToString().c_str());
    return jsonStr;
}

void MsgBuilder::parseUserLoginSucMsg(QString jsonStr, UserData& userData ,vector<UserData> &v)
{
    CJsonObject obj(jsonStr.toStdString());
    string userIdStr;
    obj.Get(string("userid"),userIdStr);
    userData.userId = QString(userIdStr.c_str());

    obj.Get(string("headid"),userData.headId);

    string nickNameStr;
    obj.Get(string("nickname"),nickNameStr);
    userData.nickName = QString(nickNameStr.c_str());

    CJsonObject users;
    obj.Get("users",users);
    for(int i = 0; i< users.GetArraySize();i++)
    {
        CJsonObject user;
        users.Get(i,user);
        UserData userData;
        string userIdStr;
        string nickNameStr;
        user.Get("userid",userIdStr);
        userData.userId = QString(userIdStr.c_str());
        user.Get("nickname",nickNameStr);
        userData.nickName = QString(nickNameStr.c_str());
        user.Get("headid",userData.headId);
        v.push_back(userData);

    }
}

QString MsgBuilder::buildUserLoginLoginLose()
{
    CJsonObject obj;
    obj.Add(string("type"),userLoginLoginLose);
    QString jsonStr(obj.ToString().c_str());
    return jsonStr;
}

QString MsgBuilder::buildUserOnlineMsg(UserData data)
{
    CJsonObject obj;
    obj.Add(string("type"),userOnline);//json串的类型
    obj.Add(string("userid"),data.userId.toStdString());
    obj.Add(string("headid"),data.headId);
    obj.Add(string("nickname"),data.nickName.toStdString());
    //c_str是string类的函数，将string类型转换成char*
    //QString的构造函数不支持string类型，支持char*
    QString jsonStr(obj.ToString().c_str());
    return jsonStr;
}

void MsgBuilder::parseUserOnlineMsg(QString jsonStr, UserData &data)
{
    CJsonObject obj(jsonStr.toStdString());
    string userIdStr;
    obj.Get(string("userid"),userIdStr);
    data.userId = QString(userIdStr.c_str());

    obj.Get(string("headid"),data.headId);

    string nickNameStr;
    obj.Get(string("nickname"),nickNameStr);
    data.nickName = QString(nickNameStr.c_str());
}

QString MsgBuilder::buildUserOfflineMsg(UserData data)
{
    CJsonObject obj;
    obj.Add(string("type"),userOffline);//json串的类型
    obj.Add(string("userid"),data.userId.toStdString());
    obj.Add(string("headid"),data.headId);
    obj.Add(string("nickname"),data.nickName.toStdString());
    //c_str是string类的函数，将string类型转换成char*
    //QString的构造函数不支持string类型，支持char*
    QString jsonStr(obj.ToString().c_str());
    return jsonStr;
}

void MsgBuilder::parseUserOfflineMsg(QString jsonStr, UserData& data)
{
    CJsonObject obj(jsonStr.toStdString());
    string userIdStr;
    obj.Get(string("userid"),userIdStr);
    data.userId = QString(userIdStr.c_str());

    obj.Get(string("headid"),data.headId);

    string nickNameStr;
    obj.Get(string("nickname"),nickNameStr);
    data.nickName = QString(nickNameStr.c_str());
}

QString MsgBuilder::buildUserSendMsg(UserData from, UserData to, QString msg)
{
    CJsonObject obj;
    obj.Add(string("type"),userSendMsg);//json串的类型
    obj.Add(string("fromUserid"),from.userId.toStdString());
    obj.Add(string("formHeadid"),from.headId);
    obj.Add(string("formNickname"),from.nickName.toStdString());

    obj.Add(string("toUserid"),to.userId.toStdString());
    obj.Add(string("toHeadid"),to.headId);
    obj.Add(string("toNickname"),to.nickName.toStdString());

    obj.Add(string("msg"),msg.toStdString());

    //c_str是string类的函数，将string类型转换成char*
    //QString的构造函数不支持string类型，支持char*
    QString jsonStr(obj.ToString().c_str());
    return jsonStr;
}

void MsgBuilder::parseUserSendMsg(QString jsonStr, UserData &from, UserData &to, QString &msg)
{
    CJsonObject obj(jsonStr.toStdString());
    /* from */
    string fromUserIdStr;
    obj.Get(string("fromUserid"),fromUserIdStr);
    from.userId = QString(fromUserIdStr.c_str());

    obj.Get(string("formHeadid"),from.headId);

    string fromNickNameStr;
    obj.Get(string("formNickname"),fromNickNameStr);
    from.nickName = QString(fromNickNameStr.c_str());

    /* to */
    string toUserIdStr;
    obj.Get(string("toUserid"),toUserIdStr);
    to.userId = QString(toUserIdStr.c_str());

    obj.Get(string("toHeadid"),to.headId);

    string toNickNameStr;
    obj.Get(string("toNickname"),toNickNameStr);
    to.nickName = QString(toNickNameStr.c_str());

    /* msg */
    string msgStr;
    obj.Get(string("msg"),msgStr);
    msg = QString(msgStr.c_str());
}

QString MsgBuilder::buildUserReceiveMsg(UserData from, UserData to, QString msg)
{
    CJsonObject obj;
    obj.Add(string("type"),userReceiveMsg);//json串的类型
    obj.Add(string("fromUserid"),from.userId.toStdString());
    obj.Add(string("formHeadid"),from.headId);
    obj.Add(string("formNickname"),from.nickName.toStdString());

    obj.Add(string("toUserid"),to.userId.toStdString());
    obj.Add(string("toHeadid"),to.headId);
    obj.Add(string("toNickname"),to.nickName.toStdString());

    obj.Add(string("msg"),msg.toStdString());

    //c_str是string类的函数，将string类型转换成char*
    //QString的构造函数不支持string类型，支持char*
    QString jsonStr(obj.ToString().c_str());
    return jsonStr;
}

void MsgBuilder::parseUserReceiveMsg(QString jsonStr, UserData &from, UserData &to, QString &msg)
{
    CJsonObject obj(jsonStr.toStdString());
    /* from */
    string fromUserIdStr;
    obj.Get(string("fromUserid"),fromUserIdStr);
    from.userId = QString(fromUserIdStr.c_str());

    obj.Get(string("formHeadid"),from.headId);

    string fromNickNameStr;
    obj.Get(string("formNickname"),fromNickNameStr);
    from.nickName = QString(fromNickNameStr.c_str());

    /* to */
    string toUserIdStr;
    obj.Get(string("toUserid"),toUserIdStr);
    to.userId = QString(toUserIdStr.c_str());

    obj.Get(string("toHeadid"),to.headId);

    string toNickNameStr;
    obj.Get(string("toNickname"),toNickNameStr);
    to.nickName = QString(toNickNameStr.c_str());

    /* msg */
    string msgStr;
    obj.Get(string("msg"),msgStr);
    msg = QString(msgStr.c_str());
}


