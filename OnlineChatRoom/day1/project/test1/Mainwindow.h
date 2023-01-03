#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

/*
MianWindow是我们自己定义的类，继承了QMainWindow
QMainWindow是Qt的主窗口类
在面向对象语言使用框架的时候，框架会给我们提供很多具备一定功能的类，但是这些类往往只具备一些基础功能
我们项目中要求的特殊功能，所以我们要继承框架中的类，然后在此基础上添加需要的特定功能
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT    //宏，定义了一些Qt元对象的属性
    /*
    宏，定义了一些Qt元对象的属性
    Q_OBJECT的派生类必须加Q_OBJECT宏，而且必须写在私有访问权限下
    C++的Class默认访问权限是private，struct的默认访问权限是public
    一般写逻辑的类是用class，表示数据类型的类用struct
    */

public:
    /*
    构造函数，explicit防止对象的隐式转换，当构造函数只用一个实参就能匹配的时候就能触发隐式转换
    隐式转换在绝大部分的情况下都是不好的
    对函数形参初始化，叫默认参数，默认参数可以不给实参
    QWidget是Qt中所有控件的基类
    parent设计到QT的内存管理机制
    */
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:      //  slots是定义槽函数的关键字，是QT的关键字，不是C++中的，c++编译器会报错,private是槽函数的访问权限，槽函数的功能仅仅比普通函数多了处理信号的功能
    void pushButton1Click();       //定义的槽函数
    void pushButton2Click();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
