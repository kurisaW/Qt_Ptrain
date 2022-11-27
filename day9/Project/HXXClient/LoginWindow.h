#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();
    
private slots:
    //函数名字以on开头，表示回调函数，既函数不是我们自己要调用。
    void onRegisterPushButtonClicked();
    void on_pushButton_connect_clicked();
    
    void on_pushButton_login_clicked();
    
    void onConnected();
    void onReadyRead();
    
private:
    void deelLoginSuc(QString jsonStr);
private:
    Ui::LoginWindow *ui;
};

#endif // LOGINWINDOW_H
