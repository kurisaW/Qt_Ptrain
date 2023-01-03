#-------------------------------------------------
#
# Project created by QtCreator 2022-11-18T09:10:49
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
    cjson/CJsonObject.cpp \
    cjson/cJSON.c \
    MsgBuilder.cpp \
    MyTcpServer.cpp \
    MyThread.cpp

HEADERS  += MainWindow.h \
    UserDao.h \
    UserEntity.h \
    cjson/cJSON.h \
    cjson/CJsonObject.hpp \
    MsgBuilder.h \
    MyTcpServer.h \
    MyThread.h

FORMS    += MainWindow.ui
