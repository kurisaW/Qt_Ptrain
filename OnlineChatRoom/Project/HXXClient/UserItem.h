#ifndef USERITEM_H
#define USERITEM_H

#include <QWidget>
#include "MsgBuilder.h"

namespace Ui {
class UserItem;
}

class UserItem : public QWidget
{
    Q_OBJECT

public:
    explicit UserItem(UserData userData,QWidget* parent = 0);
    ~UserItem();
    inline UserData getUserData()
    {
        return userData;
    }
    void addWaitMsg(QString msg);
    QStringList getWaitMsg(){return waitMsg;}//获得所有的维度信息
    void clearWaitMsg();//清空未读信息

private:
    Ui::UserItem *ui;
    UserData userData;
    QStringList waitMsg;//保存未读信息
};

#endif // USERITEM_H
