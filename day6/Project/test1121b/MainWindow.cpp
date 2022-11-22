#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QHostAddress>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server = new MyTcpServer(this);
    server->listen(QHostAddress::Any,12345);
    connect(server,SIGNAL(newConnectionForThread(qintptr)),this,SLOT(onNewConnection(qintptr)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onNewConnection(qintptr socketDescriptor)
{
    thread = new MyThread(socketDescriptor, this);
    thread->start();
}
