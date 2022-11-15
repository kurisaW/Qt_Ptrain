#include "Mainwindow.h"
// 根据.ui文件自动生成的文件，在项目的构建路径中，里卖弄包含Ui::MainWindow类
#include "ui_Mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),    //对父类部分进行初始化
    ui(new Ui::MainWindow)  //创建界面文件对象
{
    ui->setupUi(this);      //创建.ui文件中编辑的控件对象
    //因为label_hello是在.ui文件中编辑的，所以使用它需要通过ui

    /*
    连接信号与槽的函数，有5个参数
    参数1：发出信号的对象
    参数2：信号SIGNAL宏
    参数3：接收信号的对象
    参数4：处理信号的槽函数 SLOT宏

    注意：信号和槽后面都有一堆圆括号
    SIGNAL(clicked)
    */
    // this 只能用于成员函数，指向调用成员函数的对象
    connect(ui->pushButton1, SIGNAL(clicked()), this, SLOT(pushButton1Click()));
    connect(ui->pushButton2, SIGNAL(clicked()), this, SLOT(pushButton2Click()));
}

MainWindow::~MainWindow()
{
    delete ui;      //删除构造函数中创建的界面文件对象
}

void MainWindow::pushButton1Click()
{
    //QString类是QT定义的字符串处理类
    ui->label1->setText("你好");
}

void MainWindow::pushButton2Click()
{
    //QString类是QT定义的字符串处理类
    ui->label2->setText("呀");
}
