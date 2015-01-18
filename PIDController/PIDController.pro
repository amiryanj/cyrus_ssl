#-------------------------------------------------
#
# Project created by QtCreator 2014-11-09T23:18:01
#
#-------------------------------------------------

QT       += core gui serialport printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = PIDController
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    settingmanager.cpp \
    qcustomplot.cpp \
    xbeeprotocol.cpp

HEADERS  += mainwindow.h \
    settingmanager.h \
    qcustomplot.h \
    xbeeprotocol.h

FORMS    += mainwindow.ui
