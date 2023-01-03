#ifndef MSGBUILDER_H
#define MSGBUILDER_H
#include <QString>
#include <vector>

using namespace std;

//封装用户信息
struct UserData
{
    QString userId;//用户的账号
    QString nickName;//用户的昵称
    QString passwd;//用户密码
    int headId;//用户头像id，预留功能
    //因为UserData要作为map的key使用，必须是可以比较的类型,c++规定作为map中key类的必须重载<
    //<比较什么数据，随意
    bool operator<(const UserData& other)const
    {
        //这里比较UserId，所以map会根据userId进行排列
        return userId<other.userId;
    }
};
//客户端和服务器都要使用这个类
class MsgBuilder
{
public:
    //枚举，用来给常量起名，而且一个枚举中的所有常量之间是有逻辑关联的
    //枚举表示json串的种类
    enum MsgType
    {
        userLogin,//用户登录
        userRegister,//用户注册
        userRegisterRetuen,//用户注册的返回
        userLoginSuc,//用户登录成功
        userLoginLose,//用户登录失败
        userOnline,//用户上线
        userOffline,//用户下线
        userSendMsg,//用户发送消息
        userReceiveMsg,//用户接收消息
    };
    
    //因为MsgBuilder类中没有成员变量，所以的函数相对独立，
    //每个函数都是一个独立的功能，所以将成员函数定义为静态函数，静态成员函数的调用不需要对象
    //获得json串的type字段
    static MsgType getType(QString jsonStr);
    
    //构建客户端注册json串，返回值是json串
    static QString buildUserRegisterMsg(UserData data);
    static void parseUserRegisterMsg(QString jsonStr, UserData& data);
    
    //构建客户端登录json串
    static QString buildUserLoginMsg(UserData data);
    static void parseUserLoginMsg(QString jsonStr, UserData& data);

    //构建服务端的注册返回json串    返回账号给客户端
    static QString buildUSerRegisterReturnMsg(UserData data);
    static void parseUserRegisterReturnMsg(QString jsonStr, UserData& data);
    
    //构建服务端用户登录成功json串  多线程并发服务器时需要修改，暂时登录只返回类型，不携带数据
    static QString buildUserLoginSucMsg(UserData userData,vector<UserData> v);
    static void parseUserLoginSucMsg(QString jsonStr, UserData& userData, vector<UserData>& v);
    
    //构建服务端用户等式失败的json串
    static QString buildUserLoginLoseMsg();
    
    //构建用户上线json串
    static QString buildUserOnlineMsg(UserData data);
    static void parseUserOnlineMsg(QString jsonStr, UserData& data);
    
    //构建用户下线json串
    static QString buildUserOfflineMsg(UserData data);
    static void parseUserOfflineMsg(QString jsonStr, UserData& data);
    
    //构建用户发送消息的json串
    static QString buildUserSendMsg(UserData from, UserData to, QString msg);
    static void parseUserSendMsg(QString jsonStr, UserData& from, UserData& to, QString& msg);

    //构建用户接收消息json串
    static QString buildUserReceiveMsg(UserData from, UserData to, QString msg);
    static void parseUserReceiveMsg(QString jsonStr, UserData& from, UserData& to, QString& msg);
};

#endif // MSGBUILDER_H
