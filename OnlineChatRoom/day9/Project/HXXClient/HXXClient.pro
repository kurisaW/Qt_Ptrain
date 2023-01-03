#-------------------------------------------------
#
# Project created by QtCreator 2022-11-15T10:09:02
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HXXClient
TEMPLATE = app


SOURCES += main.cpp\
        LoginWindow.cpp \
    RegisterDialog.cpp \
    cjson/CJsonObject.cpp \
    cjson/cJSON.c \
    MsgBuilder.cpp \
    UserSocket.cpp \
    FriendWindow.cpp \
    UserItem.cpp \
    ChatItem.cpp \
    ChatWidget.cpp \
    ChatDialog.cpp

HEADERS  += LoginWindow.h \
    RegisterDialog.h \
    cjson/cJSON.h \
    cjson/CJsonObject.hpp \
    MsgBuilder.h \
    UserSocket.h \
    FriendWindow.h \
    UserItem.h \
    ChatItem.h \
    ChatWidget.h \
    ChatDialog.h

FORMS    += LoginWindow.ui \
    RegisterDialog.ui \
    FriendWindow.ui \
    UserItem.ui \
    ChatDialog.ui

RESOURCES += \
    images.qrc
