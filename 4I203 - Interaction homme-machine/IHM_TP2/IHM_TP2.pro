#-------------------------------------------------
#
# Project created by QtCreator 2016-01-30T18:00:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IHM_TP2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    DrawingZone.cpp

HEADERS  += mainwindow.h \
    DrawingZone.h \
    Transitions.h

FORMS    += mainwindow.ui

RESOURCES += \
    Images.qrc
