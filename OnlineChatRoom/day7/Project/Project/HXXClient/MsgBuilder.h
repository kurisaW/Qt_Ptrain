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
    //因为UserData要作为map的key使用，必须是可以比较的类型，c++规定作为map中key类的必须重载<
    //<比较什么数据随意
    bool operator <(const UserData& other) const
    {
        //这里比较userId，所以map会根据userId进行排列
        return userId<other.userId;
    }
};

//客户端和服务端都需要用到这个类
class MsgBuilder
{
public:
    //枚举，用来给常量起名字，而且一个枚举中的所有常量之间是有逻辑关联的
    enum MsgType
    {
        userRegister,//用户注册
        userLogin,//用户登录
        userRegisterReturn,
        userLoginSuc,//登陆成功
        userLoginLose//失败
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

    //构建服务端用户登录成功json串      多线程并发服务器时需要修改，暂时登录只返回类型，不携带数据
    static QString buildUserLoginSucMsg(vector<UserData> v);
    static void parseUserLoginSucMsg(QString jsonStr,vector<UserData>& v);

    //构建服务端用户登录失败json串
    static QString buildUserLoginLoseMsg();

};

#endif // MSGBUILDER_H
