#-------------------------------------------------
#
# Project created by QtCreator 2013-12-20T19:38:54
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4.9): QT += printsupport

LIBS += -lprotobuf

TARGET = Visualizer
TEMPLATE = app

INCLUDEPATH += thirdparty \
                tools

SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    plotwidget.cpp \
    fieldscene.cpp \
    graphics/graphic_bot.cpp \
    robotstate.cpp \
    tools/vector3d.cpp \
    tools/vector2d.cpp \
    packetreceiver.cpp \
    thirdparty/socket/netraw.cpp \
    thirdparty/socket/IPPacket.cpp \
    proto/cpp/ssl_world.pb.cc \
    proto/cpp/ssl_visualizer.pb.cc \
    proto/cpp/ssl_planner.pb.cc \
    proto/cpp/ssl_decision.pb.cc \
    proto/cpp/ssl_analyzer.pb.cc \
    packetparser.cpp \
    graphics/graphic_num.cpp \
    graphics/graphic_vec.cpp \
    selectcolordialog.cpp \
    graphics/graphic_plan.cpp \
    graphics/graphic_circle.cpp \
    graphics/graphic_intersect.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    plotwidget.h \
    fieldscene.h \
    graphics/graphic_bot.h \
    general.h \
    Concepts.h \
    robotstate.h \
    tools/vector3d.h \
    tools/vector2d.h \
    packetreceiver.h \
    thirdparty/socket/netraw.h \
    thirdparty/socket/IPPacket.h \
    proto/cpp/ssl_world.pb.h \
    proto/cpp/ssl_visualizer.pb.h \
    proto/cpp/ssl_planner.pb.h \
    proto/cpp/ssl_decision.pb.h \
    proto/cpp/ssl_analyzer.pb.h \
    packetparser.h \
    graphics/graphic_num.h \
    graphics/graphic_vec.h \
    selectcolordialog.h \
    graphics/graphic_plan.h \
    graphics/graphic_circle.h \
    graphics/graphic_intersect.h

FORMS    += mainwindow.ui \
    plotwidget.ui \
    fieldscene.ui \
    selectcolordialog.ui

RESOURCES += \
    icons.qrc
