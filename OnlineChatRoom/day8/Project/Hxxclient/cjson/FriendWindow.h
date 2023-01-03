#ifndef FRIENDWINDOW_H
#define FRIENDWINDOW_H

#include <QWidget>

namespace Ui {
class FriendWindow;
}

class FriendWindow : public QWidget
{
    Q_OBJECT

public:
    explicit FriendWindow(QWidget *parent = 0);
    ~FriendWindow();

private:
    Ui::FriendWindow *ui;
};

#endif // FRIENDWINDOW_H
