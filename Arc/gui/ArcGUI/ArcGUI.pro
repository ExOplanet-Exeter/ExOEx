#-------------------------------------------------
#
# Project created by QtCreator 2015-02-16T03:28:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ArcGUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    matedit.cpp \
    configure.cpp

HEADERS  += mainwindow.h \
    matedit.h \
    configure.h

FORMS    += mainwindow.ui \
    matedit.ui \
    configure.ui
