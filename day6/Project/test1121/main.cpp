#include "MainWindow.h"
#include <QApplication>
#include "MyThread.h"
#include "NetworkThread.h"
#include <QDebug>
#include <QMutex>

int source = 0;//定义全局变量，我想使用两个线程，一个对source+1执行10000次，另一个-1执行10000次
QMutex mutex;//互斥锁对象

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
//    MyThread mt;//创建线程对象
//    mt.start();//启动线程，开启线程后，子线程执行run的逻辑，会自动去执行run函数，千万不要自己调用run
//    //nt.run();//这样写是错误的！这是在主线程中执行run的逻辑。
//    NetWorkThread nt;
//    nt.start();
    
//    mt.wait();
//    nt.wait();
//    qDebug()<<source;//等两个线程都执行完毕，数组source的值
    return a.exec();
}
