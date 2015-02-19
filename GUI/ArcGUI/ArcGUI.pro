#-------------------------------------------------
#
# Project created by QtCreator 2015-02-18T03:23:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ArcGUI
TEMPLATE = app


SOURCES +=\
        mainwindow.cpp \
    configure.cpp \
    main.cpp \
    matedit.cpp

HEADERS  += mainwindow.h \
    configure.h \
    matedit.h

FORMS    += mainwindow.ui \
    configure.ui \
    matedit.ui
