#-------------------------------------------------
#
# Project created by QtCreator 2015-03-04T18:17:42
#
#-------------------------------------------------

QT       += core gui

TARGET = ObjectTracker
TEMPLATE = app

release: DESTDIR = $$PWD/../../../release_cyrus/tracker
release: MOC_DIR = $$PWD/../../../release_cyrus/tracker/mocs
release: OBJECTS_DIR = $$PWD/../../../release_cyrus/tracker/objs

debug: DESTDIR = $$PWD/../../../debug_cyrus/tracker
debug: MOC_DIR = $$PWD/../../../debug_cyrus/tracker/mocs
debug: OBJECTS_DIR = $$PWD/../../../debug_cyrus/tracker/objs

LIBS += -lprotobuf -lboost_system -lqcustomplot

SOURCES +=\
        mainwindow.cpp \
    VisionFilter.cpp \
    SSLVision.cpp \
    RobotFilter.cpp \
    NaiveKalman.cpp \
    Frame.cpp \
    BallFilter.cpp \
    ../ai/SSLWorldModel.cpp \
    ../definition/SSLObject.cpp \
    ../definition/SSLBall.cpp \
    ../definition/SSLTeam.cpp \
    ../definition/SSLRobotPhysic.cpp \
    ../definition/SSLRobot.cpp \
    ../../common/protoc/vision/cpp/messages_robocup_ssl_wrapper.pb.cc \
    ../../common/protoc/vision/cpp/messages_robocup_ssl_refbox_log.pb.cc \
    ../../common/protoc/vision/cpp/messages_robocup_ssl_geometry.pb.cc \
    ../../common/protoc/vision/cpp/messages_robocup_ssl_detection.pb.cc \
    ../../common/tools/SSLListener.cpp \
    ../../common/tools/SSLException.cpp \
    ../../common/math/vector3d.cpp \
    ../../common/math/vector2d.cpp \
    ../../common/math/sslmath.cpp \
    ../../common/thirdparty/socket/netraw.cpp \
    ../../common/thirdparty/socket/IPPacket.cpp \
    ../../visualizer/plotwidget.cpp \
    ObjectTracker.cpp \
    ../paramater-manager/parametermanager.cpp

HEADERS  += mainwindow.h \
    VisionFilter.h \
    SSLVision.h \
    RobotFilter.h \
    NaiveKalman.h \
    Frame.h \
    BallFilter.h \
    ../ai/SSLWorldModel.h \
    ../definition/SSLObject.h \
    ../definition/SSLBall.h \
    ../definition/SSLTeam.h \
    ../definition/SSLRobotPhysic.h \
    ../definition/SSLRobot.h \
    ../../common/protoc/vision/cpp/messages_robocup_ssl_wrapper.pb.h \
    ../../common/protoc/vision/cpp/messages_robocup_ssl_refbox_log.pb.h \
    ../../common/protoc/vision/cpp/messages_robocup_ssl_geometry.pb.h \
    ../../common/protoc/vision/cpp/messages_robocup_ssl_detection.pb.h \
    ../../common/tools/SSLListener.h \
    ../../common/tools/SSLException.h \
    ../../common/math/vector3d.h \
    ../../common/math/vector2d.h \
    ../../common/math/sslmath.h \
    ../../common/thirdparty/socket/netraw.h \
    ../../common/thirdparty/socket/IPPacket.h \
    ../../visualizer/plotwidget.h \
    ../paramater-manager/parametermanager.h

FORMS    += mainwindow.ui \
    ../../visualizer/plotwidget.ui
