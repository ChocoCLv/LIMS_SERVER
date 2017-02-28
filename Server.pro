#-------------------------------------------------
#
# Project created by QtCreator 2017-02-06T18:11:35
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += core
QT       += sql

QT += widgets

TARGET = Server
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    commmodule.cpp \
    databasemodule.cpp \
    requestparsemodule.cpp \
    requestbuffpool.cpp \
    logmodule.cpp \
    clientrequest.cpp

HEADERS  += mainwindow.h \
    commmodule.h \
    databasemodule.h \
    requestparsemodule.h \
    global.h \
    requestbuffpool.h \
    logmodule.h \
    clientrequest.h

FORMS    += mainwindow.ui
