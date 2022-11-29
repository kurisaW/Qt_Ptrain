#ifndef MSGBUILDER_H
#define MSGBUILDER_H
#include <QString>
#include <vector>
using namespace std;

//封装用户信息
struct UserData
{
    QString userId;//用户账号
    QString nickName;//用户昵称
    QString passwd;//用户密码
    int headId;//用户头像id，预留功能
    bool operator<(const UserData& other)const
    {
        return  userId<other.userId;
    }
};

//客户端和服务端都需要用到这个类
class MsgBuilder
{
public:
    //枚举，用来给常量起名字，而且一个美剧中的所有常量之间是有逻辑关联的
    enum MsgType
    {
        userRegister,//用户注册
        userLogin,//用户登录
        userRegisterReturn,
        userLoginSuc,//用户登录成功
        userLoginLoginLose,//用户登录失败
        userOnline,//用户上线
        userOffline,//下线
        userSendMsg,//发消息
        userReceiveMsg//收消息
    };

    //因为MsgBuild类中没有成员变量，所有的函数相对独立，每个函数都是一个独立的功能，所以将成员函数定义为静态函数
    //静态成员函数可以不需要对象

    //获得json串的type字段
    static MsgType getType(QString jsonStr);

    //构建客户端注册json字符串，返回值是json串
    static QString buildUserRegisterMsg(UserData data);//构建一个用户信息
    static void parseUserRegisterMsg(QString jsonStr,UserData& data);

    //构建客户端登录json串
    static QString buildUserLoginMsg(UserData data);
    static void parseUserLoginMsg(QString jsonStr,UserData& data);

    //构建服务端的注册返回json串   返回账号给客户端
    static QString buildUserRegisterReturnMsg(UserData data);
    static void parseUserRegisterReturnMsg(QString jsonStr, UserData& data);

    //构建客户端登录成功json串
    static QString buildUserLoginSucMsg(UserData userData ,vector<UserData> v);
    static void parseUserLoginSucMsg(QString jsonStr,UserData& userData ,vector<UserData>& v);

    //构建服务端登录失败的json串
    static QString buildUserLoginLoginLose();

    //构建用户上线json串
    static QString buildUserOnlineMsg(UserData data);
    static void parseUserOnlineMsg(QString jsonStr,UserData &data);

    //构建用户下线json串
    static QString buildUserOfflineMsg(UserData data);
    static void parseUserOfflineMsg(QString jsonStr,UserData& data);

    //构建用户发送消息的json串
    static QString buildUserSendMsg(UserData from, UserData to, QString msg);
    static void parseUserSendMsg(QString jsonStr,UserData& from, UserData& to,QString& msg);//解析json串

    //构建用户接收消息的json串
    static QString buildUserReceiveMsg(UserData from, UserData to, QString msg);
    static void parseUserReceiveMsg(QString jsonStr,UserData& from, UserData& to, QString& msg);//解析json串

};

#endif // MSGBUILDER_H
