#include "ChatDialog.h"
#include "ui_ChatDialog.h"
#include <QGridLayout>

ChatDialog::ChatDialog(UserData guestData ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChatDialog),
    guestData(guestData)
{
    ui->setupUi(this);
    initUI();
}

ChatDialog::~ChatDialog()
{
    delete ui;
}

void ChatDialog::addMsg(QString msg)
{
    //给聊天空间添加一条信息，信息是别人(guestData)发给我的
    chatWidget->addMsg(msg,guestData.headId,ChatItem::guest);
}

void ChatDialog::initUI()
{
    QString info = QString("%1(%2").arg(guestData.nickName).arg(guestData.userId);
    setWindowTitle(info);

    QGridLayout* layout = new QGridLayout(this);
    setLayout(layout);//设置窗口布局为网格布局

    //创建自定义的聊天控件
    chatWidget = new ChatWidget(this);
    layout->addWidget(chatWidget,0, 0, 1, 2);
    layout->addWidget(ui->pushButton_send, 2, 1, 1, 1);
    layout->addWidget(ui->textEdit_msg, 2, 0, 1, 1);
}

void ChatDialog::closeEvent(QCloseEvent *e)
{
    emit sigChatDialogClose(guestData);
}



void ChatDialog::on_pushButton_send_clicked()
{
    QString msg = ui->textEdit_msg->toPlainText();//获得输入信息
    UserData from = UserSocket::getInstance()->getUserData();
    UserData to = guestData;
    QString jsonStr = MsgBuilder::buildUserSendMsg(from, to, msg);
    QByteArray bdata = jsonStr.toLocal8Bit();
    UserSocket::getInstance()->write(bdata.data(),bdata.size());
}
