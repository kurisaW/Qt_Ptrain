#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(botton_click));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::botton_click()
{
    QString user = ui->lineEdit1->text();
    QString passwd = ui->lineEdit2->text();

    if (user=="admin" && passwd=="123abc")
    {
        ui->label_text->setText("登陆成功");
    }
    else
    {
        ui->label_text->setText("登录失败");
    }
}

