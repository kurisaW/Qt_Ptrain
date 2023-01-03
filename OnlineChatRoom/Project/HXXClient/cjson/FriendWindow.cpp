#include "FriendWindow.h"
#include "ui_FriendWindow.h"

FriendWindow::FriendWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FriendWindow)
{
    ui->setupUi(this);
}

FriendWindow::~FriendWindow()
{
    delete ui;
}
