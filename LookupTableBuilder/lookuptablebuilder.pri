#-------------------------------------------------
#
# Project created by QtCreator 2013-08-10T17:26:48
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += $$PWD\
               $$PWD/Logic

SOURCES +=\
    $$PWD/Controller/filecontroller.cpp \
    $$PWD/Dialogs/designdialog.cpp \
    $$PWD/Logic/graph.cpp \
    $$PWD/Ctrls/graphview.cpp \
    $$PWD/Ctrls/clickablescene.cpp

HEADERS  += \
    $$PWD/Controller/filecontroller.h \
    $$PWD/Dialogs/designdialog.h \
    $$PWD/Logic/graph.h \
    $$PWD/Ctrls/graphview.h \
    $$PWD/Ctrls/clickablescene.h

FORMS    += \
    $$PWD/Dialogs/designdialog.ui
