#-------------------------------------------------
#
# Project created by QtCreator 2022-11-18T14:40:16
#
#-------------------------------------------------

QT       += core gui
QT         += network
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Hxxclient
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    MsgBuilder.cpp \
    RegisterDialog.cpp \
    UserSocket.cpp \
    cjson/CJsonObject.cpp \
    cjson/cJSON.c \
    FriendWindow.cpp \
    UserItem.cpp \
    ChatItem.cpp \
    ChatWidget.cpp \
    ChatDialog.cpp

HEADERS  += MainWindow.h \
    MsgBuilder.h \
    RegisterDialog.h \
    UserSocket.h \
    cjson/cJSON.h \
    cjson/CJsonObject.hpp \
    FriendWindow.h \
    UserItem.h \
    ChatItem.h \
    ChatWidget.h \
    ChatDialog.h

FORMS    += \
    RegisterDialog.ui \
    MainWindow.ui \
    cjson/FriendWindow.ui \
    FriendWindow.ui \
    UserItem.ui \
    ChatDialog.ui

RESOURCES += \
    images.qrc

DISTFILES += \
    heads/head1.jpg \
    heads/head2.jpg \
    heads/head3.jpg \
    heads/head4.jpg \
    heads/head5.jpg \
    heads/head6.jpg \
    heads/head7.jpg \
    heads/head8.jpg \
    heads/head9.jpg \
    heads/head10.jpg \
    heads/head11.jpg \
    heads/head12.jpg \
    heads/head13.jpg \
    heads/head14.jpg \
    heads/head15.jpg \
    heads/head16.jpg \
    heads/head17.jpg \
    heads/head18.jpg \
    heads/head19.jpg \
    heads/head20.jpg \
    heads/head21.jpg \
    heads/head22.jpg \
    heads/head23.jpg \
    heads/head24.jpg \
    heads/head25.jpg \
    heads/head26.jpg \
    heads/head27.jpg \
    heads/head28.jpg \
    heads/head29.jpg \
    heads/head30.jpg \
    heads/head31.jpg \
    heads/head32.jpg \
    heads/v2-c4056bfa736b39931fc1d4b5fa7f09a9_r.jpg
