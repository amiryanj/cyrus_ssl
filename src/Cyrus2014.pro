#-------------------------------------------------
#
# Project created by QtCreator 2013-09-06T18:59:38
#
#-------------------------------------------------

QT       += core gui network
#QT       -= gui

LIBS += -lprotobuf


TARGET = Cyrus2014
#CONFIG   += console
#CONFIG   -= app_bundle

INCLUDEPATH += thirdparty\
                thirdparty/socket

TEMPLATE = app

SOURCES += main.cpp \
    vision/SSLVision.cpp \
    physical/SSLReferee.cpp \
    physical/RobotSerialConnection.cpp \
    thirdparty/referee/cpp/referee.pb.cc \
    thirdparty/serialib/serialib.cpp \
    thirdparty/socket/IPPacket.cpp \
    thirdparty/sslvision/cpp/messages_robocup_ssl_wrapper.pb.cc \
    thirdparty/sslvision/cpp/messages_robocup_ssl_refbox_log.pb.cc \
    thirdparty/sslvision/cpp/messages_robocup_ssl_geometry.pb.cc \
    thirdparty/sslvision/cpp/messages_robocup_ssl_detection.pb.cc \
    tools/SSLListener.cpp \
    tools/SSLException.cpp \
    ai/SSLWorldModel.cpp \
    definition/SSLTeam.cpp \
    definition/SSLRobot.cpp \
    definition/SSLObject.cpp \
    definition/SSLBall.cpp \
    definition/SSLRobotPhysic.cpp \
    ai/SSLGame.cpp \
    definition/RobotCommandPacket.cpp \
    vision/SSLRobotKalmanFilter.cpp \
    tools/vector3d.cpp \
    tools/vector2d.cpp \
    vision/frame.cpp \
    vision/VisionFilterModule.cpp \
    thirdparty/socket/netraw.cpp \
    soccer/SSLArrange.cpp \
    soccer/posts/SSLPost.cpp \
    soccer/posts/DefenderPost.cpp \
    soccer/posts/MidfielderPost.cpp \
    soccer/posts/AttackerPost.cpp \
    soccer/posts/GoaliePost.cpp \
    soccer/SSLRole.cpp \
    soccer/SSLPostManager.cpp

HEADERS += \
    vision/SSLVision.h \
    physical/SSLReferee.h \
    physical/RobotSerialConnection.h \
    thirdparty/referee/cpp/referee.pb.h \
    thirdparty/serialib/serialib.h \
    thirdparty/socket/IPPacket.h \
    thirdparty/sslvision/cpp/messages_robocup_ssl_wrapper.pb.h \
    thirdparty/sslvision/cpp/messages_robocup_ssl_refbox_log.pb.h \
    thirdparty/sslvision/cpp/messages_robocup_ssl_geometry.pb.h \
    thirdparty/sslvision/cpp/messages_robocup_ssl_detection.pb.h \
    tools/SSLListener.h \
    tools/SSLException.h \
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
    vision/SSLRobotKalmanFilter.h \
    tools/vector3d.h \
    tools/vector2d.h \
    vision/frame.h \
    vision/VisionFilterModule.h \
    thirdparty/socket/netraw.h \
    thirdparty/util.h \
    soccer/SSLArrange.h \
    soccer/posts/SSLPost.h \
    soccer/posts/DefenderPost.h \
    soccer/posts/MidfielderPost.h \
    soccer/posts/AttackerPost.h \
    soccer/posts/GoaliePost.h \
    soccer/SSLRole.h \
    soccer/SSLPostManager.h


