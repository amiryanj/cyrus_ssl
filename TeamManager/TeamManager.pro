#-------------------------------------------------
#
# Project created by QtCreator 2014-07-11T19:32:56
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS += -lprotobuf

release: DESTDIR = $$PWD/../../release_cyrus/team_manager
release: MOC_DIR = $$PWD/../../release_cyrus/team_manager/mocs
release: OBJECTS_DIR = $$PWD/../../release_cyrus/team_manager/objs
release: UI_DIR = $$PWD/../../release_cyrus/team_manager/ui

debug: DESTDIR = $$PWD/../../debug_cyrus/team_manager
debug: MOC_DIR = $$PWD/../../debug_cyrus/team_manager/mocs
debug: OBJECTS_DIR = $$PWD/../../debug_cyrus/team_manager/objs
debug: UI_DIR = $$PWD/../../debug_cyrus/team_manager/ui


TARGET = TeamManager
TEMPLATE = app

INCLUDEPATH += ../shared \
            ../shared/protoc \

SOURCES += main.cpp\
        mainwindow.cpp \
    fieldgraphicsview.cpp \
    watchfieldgraphics.cpp \
    udpsocket.cpp \
    cyrusserverpackethandler.cpp \
    ../shared/utility/vector3d.cpp \
    ../shared/utility/vector2d.cpp \
    ../shared/utility/generalmath.cpp \
    ../shared/proto/vision/cpp/messages_robocup_ssl_wrapper.pb.cc \
    ../shared/proto/vision/cpp/messages_robocup_ssl_refbox_log.pb.cc \
    ../shared/proto/vision/cpp/messages_robocup_ssl_geometry.pb.cc \
    ../shared/proto/vision/cpp/messages_robocup_ssl_detection.pb.cc

HEADERS  += mainwindow.h \
    fieldgraphicsview.h \
    watchfieldgraphics.h \
    udpsocket.h \
    cyrusserverpackethandler.h \
    ../shared/utility/vector3d.h \
    ../shared/utility/vector2d.h \
    ../shared/utility/generalmath.h \
    ../shared/proto/vision/cpp/messages_robocup_ssl_wrapper.pb.h \
    ../shared/proto/vision/cpp/messages_robocup_ssl_refbox_log.pb.h \
    ../shared/proto/vision/cpp/messages_robocup_ssl_geometry.pb.h \
    ../shared/proto/vision/cpp/messages_robocup_ssl_detection.pb.h


FORMS    += mainwindow.ui \
    watchfieldgraphics.ui

RESOURCES += \
    icons.qrc
