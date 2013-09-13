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
    vision/SSLVision.cpp \
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
    tools/MulticastListener.cpp \
    ai/SSLWorldModel.cpp \
    definition/SSLTeam.cpp \
    definition/SSLRobot.cpp \
    definition/SSLObject.cpp \
    definition/SSLBall.cpp \
    definition/SSLRobotPhysic.cpp \
    ai/SSLGame.cpp \
    definition/RobotCommandPacket.cpp \
    vision/RobotFilter.cpp

HEADERS += \
    vision/SSLVision.h \
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
    general.h \
    ai/SSLWorldModel.h \
    definition/SSLTeam.h \
    definition/SSLRobot.h \
    definition/SSLObject.h \
    definition/SSLBall.h \
    definition/SSLRobotPhysic.h \
    definition/Concepts.h \
    ai/SSLGame.h \
    definition/RobotCommandPacket.h \
    vision/RobotFilter.h

