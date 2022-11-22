#-------------------------------------------------
#
# Project created by QtCreator 2022-11-21T11:34:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test1121
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    MyThread.cpp \
    NetworkThread.cpp \
    MyThread2.cpp \
    UserData.cpp

HEADERS  += MainWindow.h \
    MyThread.h \
    NetworkThread.h \
    MyThread2.h \
    UserData.h

FORMS    += MainWindow.ui
