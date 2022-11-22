#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "MyTcpServer.h"
#include "MyThread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onNewConnection(qintptr socketDescriptor);

private:
    Ui::MainWindow *ui;
    MyTcpServer* server;
    MyThread* thread;
};

#endif // MAINWINDOW_H
