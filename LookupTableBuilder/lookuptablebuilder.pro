#-------------------------------------------------
#
# Project created by QtCreator 2013-08-10T17:26:48
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LookupTableBuilder
TEMPLATE = app


release: DESTDIR = $$PWD/../../release_cyrus/lookup_table_builder
release: MOC_DIR = $$PWD/../../release_cyrus/lookup_table_builder/mocs
release: OBJECTS_DIR = $$PWD/../../release_cyrus/lookup_table_builder/objs
release: UI_DIR = $$PWD/../../release_cyrus/lookup_table_builder/ui

debug: DESTDIR = $$PWD/../../debug_cyrus/lookup_table_builder
debug: MOC_DIR = $$PWD/../../debug_cyrus/lookup_table_builder/mocs
debug: OBJECTS_DIR = $$PWD/../../debug_cyrus/lookup_table_builder/objs
debug: UI_DIR = $$PWD/../../debug_cyrus/lookup_table_builder/ui



SOURCES +=\
    Controller/filecontroller.cpp \
    Dialogs/designdialog.cpp \
    Logic/graph.cpp \
    Ctrls/graphview.cpp \
    Ctrls/clickablescene.cpp \
    main.cpp

HEADERS  += \
    Controller/filecontroller.h \
    Dialogs/designdialog.h \
    Logic/graph.h \
    Ctrls/graphview.h \
    Ctrls/clickablescene.h

FORMS    += \
    Dialogs/designdialog.ui
