#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = 0);
    ~RegisterDialog();

private:
    void closeEvent(QCloseEvent *e);//重写基类的closeEvent，在界面关闭时会自动调用

private slots:
    void on_pushButton_register_clicked();
    void onReadyRead();

private:
    Ui::RegisterDialog *ui;
};

#endif // REGISTERDIALOG_H
