#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "MyThread2.h"
#include "UserData.h"

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
    void onThreadValue(UserData val);

private:
    Ui::MainWindow *ui;
    MyThread2* t2;
};

#endif // MAINWINDOW_H
