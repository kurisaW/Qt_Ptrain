#-------------------------------------------------
#
# Project created by QtCreator 2022-11-18T10:54:27
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HXXClient
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    MsgBuilder.cpp \
    RegisterDialog.cpp \
    UserSocket.cpp \
    cjson/CJsonObject.cpp \
    cjson/cJSON.c

HEADERS  += MainWindow.h \
    MsgBuilder.h \
    RegisterDialog.h \
    UserSocket.h \
    cjson/cJSON.h \
    cjson/CJsonObject.hpp

FORMS    += MainWindow.ui \
    RegisterDialog.ui

DISTFILES += \
    HXXClient.pro.user
