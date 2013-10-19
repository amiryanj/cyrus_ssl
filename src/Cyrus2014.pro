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
    definition/SSLPost.cpp \
    soccer/SSLPostManager.cpp \
    ai/SSLAnalyzer.cpp \
    vision/SSLBallKalmanFilter.cpp \
    gui/guimodule.cpp \
    soccer/roles/SSLRole.cpp \
    soccer/roles/keepgoal.cpp \
    definition/sslagent.cpp \
    definition/sslstrategy.cpp \
    soccer/sslstrategymanager.cpp \
    soccer/sslrolemanager.cpp

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
    definition/SSLPost.h \
    soccer/SSLPostManager.h \
    ai/SSLAnalyzer.h \
    vision/SSLBallKalmanFilter.h \
    gui/guimodule.h \
    soccer/roles/SSLRole.h \
    soccer/roles/keepgoal.h \
    definition/sslagent.h \
    definition/sslstrategy.h \
    soccer/sslstrategymanager.h \
    soccer/sslrolemanager.h


