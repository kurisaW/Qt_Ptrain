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

private:
    Ui::UserItem *ui;
    UserData userData;
};

#endif // USERITEM_H
