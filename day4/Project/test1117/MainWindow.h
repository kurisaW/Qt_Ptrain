#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
//库中的头文件在那包含的行，自定义的头文件最好在源文件包含，避免出现头文件互相包含问题。

#include <QSqlDatabase>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //成员变量如果没有特殊的考虑都应是是私有的，
    //成员函数如果不需外部调用，都应是私有，原则 访问权限越小越好
    //public写在类的上面，private写在下面，方便阅读
private slots:
    //clinet
    void onNewConnection();
    void onDisConnection();
    void onReadyRead();
    //

    //SQL
    void on_pushButton_insert_clicked();
    //

    void on_pushButton_query_clicked();

    void on_pushButton_login_clicked();

private:
    Ui::MainWindow *ui;
    //client
    QTcpServer* server;
    QTcpSocket* client;//与客户的通信的socket对象
    //

    //SQL
    QSqlDatabase db;
    //
};

#endif // MAINWINDOW_H
