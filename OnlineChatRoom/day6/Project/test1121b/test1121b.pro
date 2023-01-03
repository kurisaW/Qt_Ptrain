#-------------------------------------------------
#
# Project created by QtCreator 2022-11-21T14:22:24
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test1121b
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    MyTcpServer.cpp \
    MyThread.cpp

HEADERS  += MainWindow.h \
    MyTcpServer.h \
    MyThread.h

FORMS    += MainWindow.ui
