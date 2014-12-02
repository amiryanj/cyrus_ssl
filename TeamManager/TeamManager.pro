#-------------------------------------------------
#
# Project created by QtCreator 2014-07-11T19:32:56
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS += -lprotobuf

TARGET = TeamManager
TEMPLATE = app

INCLUDEPATH += ../common \
            ../common/protoc \

SOURCES += main.cpp\
        mainwindow.cpp \
    fieldgraphicsview.cpp \
    watchfieldgraphics.cpp \
    udpsocket.cpp \
    cyrusserverpackethandler.cpp \
    ../common/math/vector3d.cpp \
    ../common/math/vector2d.cpp \
    ../common/math/sslmath.cpp \
    ../common/protoc/vision/cpp/messages_robocup_ssl_wrapper.pb.cc \
    ../common/protoc/vision/cpp/messages_robocup_ssl_refbox_log.pb.cc \
    ../common/protoc/vision/cpp/messages_robocup_ssl_geometry.pb.cc \
    ../common/protoc/vision/cpp/messages_robocup_ssl_detection.pb.cc

HEADERS  += mainwindow.h \
    fieldgraphicsview.h \
    watchfieldgraphics.h \
    general.h \
    udpsocket.h \
    cyrusserverpackethandler.h \
    ../common/math/vector3d.h \
    ../common/math/vector2d.h \
    ../common/math/sslmath.h \
    ../common/protoc/vision/cpp/messages_robocup_ssl_wrapper.pb.h \
    ../common/protoc/vision/cpp/messages_robocup_ssl_refbox_log.pb.h \
    ../common/protoc/vision/cpp/messages_robocup_ssl_geometry.pb.h \
    ../common/protoc/vision/cpp/messages_robocup_ssl_detection.pb.h


FORMS    += mainwindow.ui \
    watchfieldgraphics.ui

RESOURCES += \
    icons.qrc
