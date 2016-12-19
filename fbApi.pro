#-------------------------------------------------
#
# Project created by QtCreator 2016-12-11T18:35:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network webenginewidgets webview

TARGET = fbApi
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    fbconnect.cpp \
    fbloginwidget.cpp \
    form.cpp \
    friends.cpp

HEADERS  += widget.h \
    fbconnect.h \
    fbloginwidget.h \
    form.h \
    friends.h

FORMS    += widget.ui \
    fbloginwidget.ui \
    form.ui \
    friends.ui

DISTFILES += \
    help.txt
