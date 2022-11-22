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

QString MsgBuilder::buildUserLoginSucMsg()
{
    CJsonObject obj;
    obj.Add(string("type"),userLoginSuc);
    QString jsonStr(obj.ToString().c_str());
    return jsonStr;
}

QString MsgBuilder::buildUserLoginLoseMsg()
{
    CJsonObject obj;
    obj.Add(string("type"),userLoginLose);
    QString jsonStr(obj.ToString().c_str());
    return jsonStr;
}


