#include "Mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    /*
    QApplication是QT的应用类，包含的内容很多，之所以这么命名是为了避免命名污染
    C++的命名空间，专门为了解决命名问题
    QT中给每个类前面加了Q，相当于命名空间的功能
    这样做的好处是为了更好兼容其他没有命名空间的语言，如python
    */

    QApplication a(argc, argv);
    MainWindow w;       //创建项目的第一个窗口对象
    w.show();           //显示第一个窗口

    return a.exec();    //执行应用
}
