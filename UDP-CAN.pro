#-------------------------------------------------
#
# Project created by QtCreator 2018-09-11T13:14:34
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ECAN-E01S
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tcp_client.cpp

HEADERS  += mainwindow.h \
    main.h \
    tcp_client.h \
    testrawdata.h

FORMS    += mainwindow.ui
