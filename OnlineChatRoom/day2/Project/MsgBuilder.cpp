#include "MsgBuilder.h"
#include "cjson/CJsonObject.hpp"
#include <string>//cjson支持c++string

using namespace neb;
using namespace std;

QString MsgBuilder::buildUserRegisterMsg(UserData data)
{
    CJsonObject obj;
    obj.Add("type",userRegister);//用于区分json串类型
    obj.Add(string("nickname"),data.nickName.toStdString());
    obj.Add(string("passwd"),data.passwd.toStdString());
    obj.Add(string("headid"),data.headId);
    QString jsonStr(obj.ToString().c_str());
    //c_str是string类的函数，将string类型转换成char*
    //QString的构造函数不支持string类型，支持char*
    return jsonStr;
}

void MsgBuilder::parseUserRegisterMsg(QString jsonStr, UserData &data)
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
