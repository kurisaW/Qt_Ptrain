#-------------------------------------------------
#
# Project created by QtCreator 2022-11-18T09:11:07
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HXXServer
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    UserDao.cpp \
    UserEntity.cpp \
    MsgBuilder.cpp \
    cjson/CJsonObject.cpp \
    cjson/cJSON.c \
    MyTcpServer.cpp \
    MyThread.cpp

HEADERS  += MainWindow.h \
    UserDao.h \
    UserEntity.h \
    MsgBuilder.h \
    cjson/cJSON.h \
    cjson/CJsonObject.hpp \
    MyTcpServer.h \
    MyThread.h

FORMS    += MainWindow.ui
