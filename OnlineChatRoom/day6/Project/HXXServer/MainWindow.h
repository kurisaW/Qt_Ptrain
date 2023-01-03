#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>

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
    void onNewConnection();//客户端新的连接
    //并发服务器时需要修改
    void onDisconnected();
    void onReadyRead();
    //end

private:
    //并发服务器时需要修改
    void deelUserRegister(QString jsonStr);//处理用户注册

    void deelUserLogin(QString jsonStr);

    //end

private:
    Ui::MainWindow *ui;
    QTcpServer* server;
    QTcpSocket* client;
};

#endif // MAINWINDOW_H
