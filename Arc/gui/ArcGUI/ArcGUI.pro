#-------------------------------------------------
#
# Project created by QtCreator 2015-02-15T15:43:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ArcGUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    configure.cpp \
    matedit.cpp

HEADERS  += mainwindow.h \
    configure.h \
    matedit.h

FORMS    += mainwindow.ui \
    configure.ui \
    matedit.ui
