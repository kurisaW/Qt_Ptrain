#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "RegisterDialog.h" //包含头文件目的是为了声明

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_register,SIGNAL(clicked()),this,SLOT(onRegisterButtonClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onRegisterButtonClicked()
{
    // new+类型名：表示在堆空间中创建一个该类型的对象，返回一个指向该对象的指针。堆空间的对象没有名字
    //this指向调用成员函数的对象，在这里this指向的是MainWindows对象
    RegisterDialog* rd = new RegisterDialog(this);
    //显示窗口
    //1、普通显示
//    rd->show();
    //2、模态显示
    rd->exec();//程序会阻塞，等界面关闭，才继续执行,使用模态显示必须指定父节点
}
