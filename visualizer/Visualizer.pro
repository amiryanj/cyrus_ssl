#-------------------------------------------------
#
# Project created by QtCreator 2013-12-20T19:38:54
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4.9): QT += printsupport

release: DESTDIR = $$PWD/../../release_cyrus/visualizer
release: MOC_DIR = $$PWD/../../release_cyrus/visualizer/mocs
release: OBJECTS_DIR = $$PWD/../../release_cyrus/visualizer/objs

debug: DESTDIR = $$PWD/../../debug_cyrus/visualizer
debug: MOC_DIR = $$PWD/../../debug_cyrus/visualizer/mocs
debug: OBJECTS_DIR = $$PWD/../../debug_cyrus/visualizer/objs

LIBS += -lprotobuf -lboost_system -lboost_filesystem

TARGET = Visualizer
TEMPLATE = app

INCLUDEPATH += ../common \
                ../common/thirdparty \
                ../common/math \
                ../common/tools \
                ../common/protoc

SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    plotwidget.cpp \
    fieldscene.cpp \
    graphics/graphic_bot.cpp \
    robotstate.cpp \
    packetreceiver.cpp \
    ../common/math/vector3d.cpp \
    ../common/math/vector2d.cpp \
    ../common/thirdparty/socket/netraw.cpp \
    ../common/thirdparty/socket/IPPacket.cpp \
    packetparser.cpp \
    graphics/graphic_num.cpp \
    graphics/graphic_vec.cpp \
    selectcolordialog.cpp \
    graphics/graphic_plan.cpp \
    graphics/graphic_circle.cpp \
    graphics/graphic_intersect.cpp \
    selectplotdialog.cpp \
    graphics/graphic_ball.cpp \
    robotpropertieswidget.cpp \
    ../common/protoc/visualizer/cpp/ssl_world.pb.cc \
    ../common/protoc/visualizer/cpp/ssl_visualizer.pb.cc \
    ../common/protoc/visualizer/cpp/ssl_planner.pb.cc \
    ../common/protoc/visualizer/cpp/ssl_decision.pb.cc \
    ../common/protoc/visualizer/cpp/ssl_analyzer.pb.cc \
    ../common/math/sslmath.cpp \
    fieldview.cpp \
    ../server/paramater-manager/parametermanager.cpp \
    graphics/graphic_arc.cpp \
    scatterplotwidget.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    plotwidget.h \
    fieldscene.h \
    graphics/graphic_bot.h \
    Concepts.h \
    robotstate.h \
    packetreceiver.h \
    ../common/math/vector2d.h \
    ../common/math/vector3d.h \
    ../common/thirdparty/socket/netraw.h \
    ../common/thirdparty/socket/IPPacket.h \
    packetparser.h \
    graphics/graphic_num.h \
    graphics/graphic_vec.h \
    selectcolordialog.h \
    graphics/graphic_plan.h \
    graphics/graphic_circle.h \
    graphics/graphic_intersect.h \
    selectplotdialog.h \
    graphics/graphic_ball.h \
    robotpropertieswidget.h \
    ../common/protoc/visualizer/cpp/ssl_world.pb.h \
    ../common/protoc/visualizer/cpp/ssl_visualizer.pb.h \
    ../common/protoc/visualizer/cpp/ssl_planner.pb.h \
    ../common/protoc/visualizer/cpp/ssl_decision.pb.h \
    ../common/protoc/visualizer/cpp/ssl_analyzer.pb.h \
    ../common/math/sslmath.h \
    fieldview.h \
    ../server/paramater-manager/parametermanager.h \
    graphics/graphic_arc.h \
    scatterplotwidget.h

FORMS    += mainwindow.ui \
    plotwidget.ui \
    fieldscene.ui \
    selectcolordialog.ui \
    selectplotdialog.ui \
    robotpropertieswidget.ui \
    scatterplotwidget.ui

RESOURCES += \
    icons.qrc
