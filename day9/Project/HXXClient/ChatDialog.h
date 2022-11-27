#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>
#include "ChatWidget.h"
#include "MsgBuilder.h"

namespace Ui {
class ChatDialog;
}

class ChatDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ChatDialog(UserData guestData, QWidget *parent = 0);
    ~ChatDialog();
    
    inline UserData getGuestData(){return guestData;}
    void addMsg(QString msg);
signals:
    void sigChatDialogClose(UserData userData);//关闭窗口信号
private slots:
    void on_pushButton_send_clicked();
    
private:
    void initUI();//初始化界面
    void closeEvent(QCloseEvent *e);//关闭窗口的事件
private:
    Ui::ChatDialog *ui;
    ChatWidget* chatWidget;//聊天控件
    UserData guestData;//对方的信息
};

#endif // CHATDIALOG_H
