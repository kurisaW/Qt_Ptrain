/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_loginpw;
    QLineEdit *lineEdit_nickname;
    QLineEdit *lineEdit_passwd;
    QLineEdit *lineEdit_headid;
    QPushButton *pushButton_insert;
    QPushButton *pushButton_query;
    QListWidget *listWidget_users;
    QLineEdit *lineEdit_loginid;
    QLabel *label_info;
    QPushButton *pushButton_login;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(440, 493);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lineEdit_loginpw = new QLineEdit(centralWidget);
        lineEdit_loginpw->setObjectName(QStringLiteral("lineEdit_loginpw"));

        gridLayout->addWidget(lineEdit_loginpw, 7, 0, 1, 2);

        lineEdit_nickname = new QLineEdit(centralWidget);
        lineEdit_nickname->setObjectName(QStringLiteral("lineEdit_nickname"));

        gridLayout->addWidget(lineEdit_nickname, 1, 0, 1, 2);

        lineEdit_passwd = new QLineEdit(centralWidget);
        lineEdit_passwd->setObjectName(QStringLiteral("lineEdit_passwd"));

        gridLayout->addWidget(lineEdit_passwd, 2, 0, 1, 2);

        lineEdit_headid = new QLineEdit(centralWidget);
        lineEdit_headid->setObjectName(QStringLiteral("lineEdit_headid"));

        gridLayout->addWidget(lineEdit_headid, 3, 0, 1, 2);

        pushButton_insert = new QPushButton(centralWidget);
        pushButton_insert->setObjectName(QStringLiteral("pushButton_insert"));

        gridLayout->addWidget(pushButton_insert, 4, 0, 1, 1);

        pushButton_query = new QPushButton(centralWidget);
        pushButton_query->setObjectName(QStringLiteral("pushButton_query"));

        gridLayout->addWidget(pushButton_query, 4, 1, 1, 1);

        listWidget_users = new QListWidget(centralWidget);
        listWidget_users->setObjectName(QStringLiteral("listWidget_users"));

        gridLayout->addWidget(listWidget_users, 5, 0, 1, 2);

        lineEdit_loginid = new QLineEdit(centralWidget);
        lineEdit_loginid->setObjectName(QStringLiteral("lineEdit_loginid"));

        gridLayout->addWidget(lineEdit_loginid, 6, 0, 1, 2);

        label_info = new QLabel(centralWidget);
        label_info->setObjectName(QStringLiteral("label_info"));

        gridLayout->addWidget(label_info, 0, 0, 1, 1);

        pushButton_login = new QPushButton(centralWidget);
        pushButton_login->setObjectName(QStringLiteral("pushButton_login"));

        gridLayout->addWidget(pushButton_login, 8, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 440, 26));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        lineEdit_loginpw->setPlaceholderText(QApplication::translate("MainWindow", "\345\257\206\347\240\201", 0));
        lineEdit_nickname->setPlaceholderText(QApplication::translate("MainWindow", "\347\224\250\346\210\267\345\220\215", 0));
        lineEdit_passwd->setPlaceholderText(QApplication::translate("MainWindow", "\345\257\206\347\240\201", 0));
        lineEdit_headid->setPlaceholderText(QApplication::translate("MainWindow", "\345\244\264\345\203\217", 0));
        pushButton_insert->setText(QApplication::translate("MainWindow", "\346\217\222\345\205\245\346\225\260\346\215\256", 0));
        pushButton_query->setText(QApplication::translate("MainWindow", "\346\237\245\350\257\242", 0));
        lineEdit_loginid->setPlaceholderText(QApplication::translate("MainWindow", "\350\264\246\345\217\267", 0));
        label_info->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        pushButton_login->setText(QApplication::translate("MainWindow", "\347\231\273\345\275\225", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
