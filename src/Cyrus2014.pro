#-------------------------------------------------
#
# Project created by QtCreator 2013-09-06T18:59:38
#
#-------------------------------------------------

QT       += core gui
#QT       -= gui

LIBS += -lprotobuf

TARGET = Cyrus2014
#CONFIG   += console
#CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    definition/WorldModel.cpp \
    definition/SSLRobotPacket.cpp \
    definition/Position.cpp \
    physical/SSLVision.cpp \
    physical/SSLReferee.cpp \
    physical/RobotSerialConnection.cpp \
    thirdparty/referee/cpp/referee.pb.cc \
    thirdparty/serialib/serialib.cpp \
    thirdparty/socket/PracticalSocket.cpp \
    thirdparty/socket/MulticastReciever.cpp \
    thirdparty/socket/IPPacket.cpp \
    thirdparty/sslvision/cpp/messages_robocup_ssl_wrapper.pb.cc \
    thirdparty/sslvision/cpp/messages_robocup_ssl_refbox_log.pb.cc \
    thirdparty/sslvision/cpp/messages_robocup_ssl_geometry.pb.cc \
    thirdparty/sslvision/cpp/messages_robocup_ssl_detection.pb.cc \
    tools/SSLListener.cpp \
    tools/SSLException.cpp \
    tools/MulticastListener.cpp

HEADERS += \
    definition/WorldModel.h \
    definition/SSLRobotPacket.h \
    definition/Position.h \
    definition/Color.h \
    physical/SSLVision.h \
    physical/SSLReferee.h \
    physical/RobotSerialConnection.h \
    thirdparty/referee/cpp/referee.pb.h \
    thirdparty/serialib/serialib.h \
    thirdparty/socket/PracticalSocket.h \
    thirdparty/socket/MulticastReciever.h \
    thirdparty/socket/IPPacket.h \
    thirdparty/sslvision/cpp/messages_robocup_ssl_wrapper.pb.h \
    thirdparty/sslvision/cpp/messages_robocup_ssl_refbox_log.pb.h \
    thirdparty/sslvision/cpp/messages_robocup_ssl_geometry.pb.h \
    thirdparty/sslvision/cpp/messages_robocup_ssl_detection.pb.h \
    tools/SSLListener.h \
    tools/SSLException.h \
    tools/MulticastListener.h \
    general.h

