#-------------------------------------------------
#
# Project created by QtCreator 2017-07-11T09:16:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenSSDUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    nvme_low_lib.c \
    OpenSSD.cpp \
    OpenSSD_API.cpp

HEADERS  += mainwindow.h \
    nvme_low_lib.h \
    nvme_internal.h \
    OpenSSD.h \
    OpenSSD_API.h

FORMS    += mainwindow.ui
