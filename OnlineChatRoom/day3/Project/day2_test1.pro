#-------------------------------------------------
#
# Project created by QtCreator 2022-11-15T10:04:49
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = day2_test1
TEMPLATE = app


SOURCES += main.cpp\
    RegisterDialog.cpp \
    MainWindow.cpp \
    cjson/CJsonObject.cpp \
    cjson/cJSON.c \
    MsgBuilder.cpp \
    UserSocket.cpp

HEADERS  += \
    RegisterDialog.h \
    MainWindow.h \
    cjson/cJSON.h \
    cjson/CJsonObject.hpp \
    MsgBuilder.h \
    UserSocket.h \
    MainWindow.h.autosave

FORMS    += \
    MainWindow.ui \
    RegisterDialog.ui

DISTFILES +=
