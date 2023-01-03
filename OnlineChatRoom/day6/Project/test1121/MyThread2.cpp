#include "MyThread2.h"
#include "UserData.h"

MyThread2::MyThread2(QObject* parent):
    QThread(parent)
{

}

void MyThread2::run()
{
    //让mainwindow中的label显示run中的i值，应该将i值传给MainWindow，使用信号传
    for(int i = 0; i<10; i++)
    {
        //emit关键字时QT的关键字，用来发送信号
        UserData data("小明",i);
        emit threadValue(data);//i作为信号的实参
        sleep(1);
    }
}
