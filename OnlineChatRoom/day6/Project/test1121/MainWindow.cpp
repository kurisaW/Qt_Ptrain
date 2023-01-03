#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qRegisterMetaType<UserData>("UserData");
    ui->setupUi(this);
    t2 = new MyThread2(this);
    connect(t2, SIGNAL(threadValue(UserData)),this,SLOT(onThreadValue(UserData)));
    t2->start();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onThreadValue(UserData val)
{
    QString data = QString("名字:%1 id:%2").arg(val.name).arg(val.id);
    ui->label_num->setText(data);
}
