#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//
#include <QTcpServer>
#include <QTcpSocket>
//在头文件中包含头文件还是在源文件中包含头文件
//自定义的头文件最好在源文件中保存，比卖你出现头文件互相包含的问题
//

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    //成员变量，如果没有特殊考虑，都应该是私有的
    //成员函数，如果不需要外部调用，都应该是私有的，原则：访问权限越小越好
    //我们会把共有权限的成员写在类的上面，私有和受保护的写下面，方便阅读代码
private slots:
    // 函数名以on开头一般代表回调
    void onRegisterButtonClicked();

    void on_pushButton_login_clicked();
    void on_pushButton_connect_clicked();

    void onConnected();
    void onReadyRead();


private:
    void deelLoginsuc(QString jsonStr);
private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
