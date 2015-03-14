#-------------------------------------------------
#
# Project created by QtCreator 2015-03-04T18:17:42
#
#-------------------------------------------------

QT       += core gui

TARGET = ObjectTracker
TEMPLATE = app

release: DESTDIR = $$PWD/../../release_cyrus/tracker
release: MOC_DIR = $$PWD/../../release_cyrus/tracker/mocs
release: OBJECTS_DIR = $$PWD/../../release_cyrus/tracker/objs

debug: DESTDIR = $$PWD/../../debug_cyrus/tracker
debug: MOC_DIR = $$PWD/../../debug_cyrus/tracker/mocs
debug: OBJECTS_DIR = $$PWD/../../debug_cyrus/tracker/objs

LIBS += -lprotobuf -lboost_system -lqcustomplot

SOURCES += \
    mainwindow.cpp \
    ObjectTracker.cpp \
    ../server/vision/VisionFilter.cpp \
    ../server/vision/SSLVision.cpp \
    ../server/vision/RobotFilter.cpp \
    ../server/vision/NaiveKalman.cpp \
    ../server/vision/Frame.cpp \
    ../server/vision/BallFilter.cpp \
    ../server/ai/SSLWorldModel.cpp \
    ../server/definition/SSLObject.cpp \
    ../server/definition/SSLBall.cpp \
    ../server/definition/SSLTeam.cpp \
    ../server/definition/SSLRobotPhysic.cpp \
    ../server/definition/SSLRobot.cpp \
    ../common/protoc/vision/cpp/messages_robocup_ssl_wrapper.pb.cc \
    ../common/protoc/vision/cpp/messages_robocup_ssl_refbox_log.pb.cc \
    ../common/protoc/vision/cpp/messages_robocup_ssl_geometry.pb.cc \
    ../common/protoc/vision/cpp/messages_robocup_ssl_detection.pb.cc \
    ../common/tools/SSLListener.cpp \
    ../common/tools/SSLException.cpp \
    ../common/math/vector3d.cpp \
    ../common/math/vector2d.cpp \
    ../common/math/sslmath.cpp \
    ../common/thirdparty/socket/netraw.cpp \
    ../common/thirdparty/socket/IPPacket.cpp \
    ../visualizer/plotwidget.cpp \
    ../server/paramater-manager/parametermanager.cpp \
    ../server/vision/robocup_ssl_client.cpp

HEADERS  += \
    mainwindow.h \
    ../server/vision/VisionFilter.h \
    ../server/vision/SSLVision.h \
    ../server/vision/RobotFilter.h \
    ../server/vision/NaiveKalman.h \
    ../server/vision/Frame.h \
    ../server/vision/BallFilter.h \
    ../server/ai/SSLWorldModel.h \
    ../server/definition/SSLObject.h \
    ../server/definition/SSLBall.h \
    ../server/definition/SSLTeam.h \
    ../server/definition/SSLRobotPhysic.h \
    ../server/definition/SSLRobot.h \
    ../common/protoc/vision/cpp/messages_robocup_ssl_wrapper.pb.h \
    ../common/protoc/vision/cpp/messages_robocup_ssl_refbox_log.pb.h \
    ../common/protoc/vision/cpp/messages_robocup_ssl_geometry.pb.h \
    ../common/protoc/vision/cpp/messages_robocup_ssl_detection.pb.h \
    ../common/tools/SSLListener.h \
    ../common/tools/SSLException.h \
    ../common/math/vector3d.h \
    ../common/math/vector2d.h \
    ../common/math/sslmath.h \
    ../common/thirdparty/socket/netraw.h \
    ../common/thirdparty/socket/IPPacket.h \
    ../visualizer/plotwidget.h \
    ../server/paramater-manager/parametermanager.h \
    ../server/vision/robocup_ssl_client.h

FORMS    += mainwindow.ui \
    ../visualizer/plotwidget.ui
