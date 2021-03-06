#-------------------------------------------------
#
# Project created by QtCreator 2016-11-29T22:14:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += network widgets

TARGET = gpioTestGui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    client.cpp \
    server.cpp \
    checkclient.cpp \

HEADERS  += mainwindow.h \
    server.h \
    client.h \
    globals.h \
    checkclient.h \

FORMS    += mainwindow.ui

LIBS += -lws2_32
