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

LIBS += -lprotobuf -lboost_system -lboost_filesystem -lqcustomplot

SOURCES += \
    mainwindow.cpp \
    ObjectTracker.cpp \
    ../server/vision/VisionFilter.cpp \
    ../server/vision/SSLVision.cpp \
    ../server/vision/RobotFilter.cpp \
    ../server/vision/NaiveKalman.cpp \    
    ../server/vision/BallFilter.cpp \
    ../server/ai/SSLWorldModel.cpp \
    ../server/definition/SSLBall.cpp \
    ../server/definition/SSLTeam.cpp \
    ../server/definition/SSLRobot.cpp \
    ../shared/proto/vision/cpp/messages_robocup_ssl_wrapper.pb.cc \
    ../shared/proto/vision/cpp/messages_robocup_ssl_refbox_log.pb.cc \
    ../shared/proto/vision/cpp/messages_robocup_ssl_geometry.pb.cc \
    ../shared/proto/vision/cpp/messages_robocup_ssl_detection.pb.cc \
    ../shared/utility/vector3d.cpp \
    ../shared/utility/vector2d.cpp \
    ../shared/utility/generalmath.cpp \
    ../shared/tools/socket/netraw.cpp \
    ../visualizer/plot-manager/plotwidget.cpp \
    ../server/paramater-manager/parametermanager.cpp \
    ../server/vision/robocup_ssl_client.cpp \
    ../server/vision/sslframe.cpp \
    ../server/vision/alphabetafilter.cpp \
    ../server/log-tools/networkplotter.cpp \
    ../shared/proto/plotter/cpp/message_plotter.pb.cc

HEADERS  += \
    mainwindow.h \
    ../server/vision/VisionFilter.h \
    ../server/vision/SSLVision.h \
    ../server/vision/RobotFilter.h \
    ../server/vision/NaiveKalman.h \    
    ../server/vision/BallFilter.h \
    ../server/ai/SSLWorldModel.h \
    ../server/definition/SSLObject.h \
    ../server/definition/SSLBall.h \
    ../server/definition/SSLTeam.h \
    ../server/definition/SSLRobot.h \
    ../shared/proto/vision/cpp/messages_robocup_ssl_wrapper.pb.h \
    ../shared/proto/vision/cpp/messages_robocup_ssl_refbox_log.pb.h \
    ../shared/proto/vision/cpp/messages_robocup_ssl_geometry.pb.h \
    ../shared/proto/vision/cpp/messages_robocup_ssl_detection.pb.h \
    ../shared/tools/ssllistener.h \
    ../shared/tools/SSLException.h \
    ../shared/utility/vector3d.h \
    ../shared/utility/vector2d.h \
    ../shared/utility/generalmath.h \
    ../shared/tools/socket/netraw.h \
    ../shared/tools/socket/ippacket.h \
    ../visualizer/plot-manager/plotwidget.h \
    ../server/paramater-manager/parametermanager.h \
    ../server/vision/robocup_ssl_client.h \
    ../server/vision/sslframe.h \
    ../server/vision/alphabetafilter.h \
    ../server/log-tools/networkplotter.h \
    ../shared/proto/plotter/cpp/message_plotter.pb.h

FORMS    += mainwindow.ui \
    ../visualizer/plot-manager/plotwidget.ui

OTHER_FILES += \
    ../settings/*.json
