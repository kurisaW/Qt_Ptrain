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
    // 函数名以on开头一般代表回调
    void onRegisterButtonClicked();

private:
    Ui::LoginWindow *ui;
};

#endif // LOGINWINDOW_H
