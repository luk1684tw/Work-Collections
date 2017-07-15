#-------------------------------------------------
#
# Project created by QtCreator 2016-06-07T21:27:08
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
DESTDIR   = $$PWD

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Final
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    chariot.cpp \
    chariot_down.cpp \
    chariot_left.cpp \
    chariot_up.cpp \
    easymusic.cpp \
    things.cpp \
    second.cpp

HEADERS  += mainwindow.h \
    chariot.h \
    chariot_down.h \
    chariot_left.h \
    chariot_up.h \
    easymusic.h \
    things.h \
    second.h

RESOURCES += \
    resource.qrc
