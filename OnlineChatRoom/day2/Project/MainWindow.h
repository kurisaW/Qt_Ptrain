#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    // 函数名以on开头一般代表回调
    void onRegisterButtonClicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
