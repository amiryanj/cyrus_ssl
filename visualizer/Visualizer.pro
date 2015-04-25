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
release: UI_DIR = $$PWD/../../release_cyrus/visualizer/ui

debug: DESTDIR = $$PWD/../../debug_cyrus/visualizer
debug: MOC_DIR = $$PWD/../../debug_cyrus/visualizer/mocs
debug: OBJECTS_DIR = $$PWD/../../debug_cyrus/visualizer/objs
debug: UI_DIR = $$PWD/../../release_cyrus/visualizer/ui

LIBS += -lprotobuf -lboost_system -lboost_filesystem

TARGET = Visualizer
TEMPLATE = app

INCLUDEPATH += ../shared \
                ../shared/utility \
                ../shared/tools \
                ../shared/proto

SOURCES += main.cpp\
        mainwindow.cpp \
    plot-manager/qcustomplot.cpp \
    plot-manager/plotwidget.cpp \
    fieldscene.cpp \
    graphics/graphic_bot.cpp \
    robotstate.cpp \
    packetreceiver.cpp \
    ../shared/utility/vector3d.cpp \
    ../shared/utility/vector2d.cpp \
    ../shared/tools/socket/netraw.cpp \
    packetparser.cpp \
    graphics/graphic_num.cpp \
    graphics/graphic_vec.cpp \
    graphics/graphic_plan.cpp \
    graphics/graphic_circle.cpp \
    graphics/graphic_intersect.cpp \
    selectplotdialog.cpp \
    graphics/graphic_ball.cpp \
    robotpropertieswidget.cpp \
    ../shared/proto/visualizer/cpp/ssl_world.pb.cc \
    ../shared/proto/visualizer/cpp/ssl_visualizer.pb.cc \
    ../shared/proto/visualizer/cpp/ssl_planner.pb.cc \
    ../shared/proto/visualizer/cpp/ssl_decision.pb.cc \
    ../shared/proto/visualizer/cpp/ssl_analyzer.pb.cc \
    ../shared/utility/generalmath.cpp \
    fieldview.cpp \
    ../server/paramater-manager/parametermanager.cpp \
    graphics/graphic_arc.cpp \
    plot-manager/scatterplotwidget.cpp \
    plot-manager/plotmanagerwidget.cpp \
    ../shared/proto/plotter/cpp/message_plotter.pb.cc

HEADERS  += mainwindow.h \
    plot-manager/qcustomplot.h \
    plot-manager/plotwidget.h \
    fieldscene.h \
    graphics/graphic_bot.h \
    Concepts.h \
    robotstate.h \
    packetreceiver.h \
    ../shared/utility/vector2d.h \
    ../shared/utility/vector3d.h \
    ../shared/tools/socket/netraw.h \
    ../shared/tools/socket/IPPacket.h \
    packetparser.h \
    graphics/graphic_num.h \
    graphics/graphic_vec.h \
    graphics/graphic_plan.h \
    graphics/graphic_circle.h \
    graphics/graphic_intersect.h \
    selectplotdialog.h \
    graphics/graphic_ball.h \
    robotpropertieswidget.h \
    ../shared/proto/visualizer/cpp/ssl_world.pb.h \
    ../shared/proto/visualizer/cpp/ssl_visualizer.pb.h \
    ../shared/proto/visualizer/cpp/ssl_planner.pb.h \
    ../shared/proto/visualizer/cpp/ssl_decision.pb.h \
    ../shared/proto/visualizer/cpp/ssl_analyzer.pb.h \
    ../shared/utility/generalmath.h \
    fieldview.h \
    ../server/paramater-manager/parametermanager.h \
    graphics/graphic_arc.h \
    plot-manager/scatterplotwidget.h \
    plot-manager/plotmanagerwidget.h \
    ../shared/proto/plotter/cpp/message_plotter.pb.h

FORMS    += mainwindow.ui \
    plot-manager/plotwidget.ui \
    fieldscene.ui \
    selectplotdialog.ui \
    robotpropertieswidget.ui \
    plot-manager/scatterplotwidget.ui \
    plot-manager/plotmanagerwidget.ui

RESOURCES += \
    icons.qrc
