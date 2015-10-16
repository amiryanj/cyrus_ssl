#-------------------------------------------------
#
# Project created by QtCreator 2013-09-06T18:59:38
#
#-------------------------------------------------

QT      += core network
greaterThan(QT_MAJOR_VERSION, 4.0): QT += widgets printsupport
greaterThan(QT_MAJOR_VERSION, 4.9): QT += serialport concurrent

#QT       -= gui

LIBS += -lprotobuf -lboost_system -lboost_filesystem -lBox2D -lqcustomplot

DEFINES += _USE_BOX2D_

release: DESTDIR = $$PWD/../../release_cyrus/server_gui
release: MOC_DIR = $$PWD/../../release_cyrus/server_gui/mocs
release: OBJECTS_DIR = $$PWD/../../release_cyrus/server_gui/objs
release: UI_DIR = $$PWD/../../release_cyrus/server_gui/ui

debug: DESTDIR = $$PWD/../../debug_cyrus/server_gui
debug: MOC_DIR = $$PWD/../../debug_cyrus/server_gui/mocs
debug: OBJECTS_DIR = $$PWD/../../debug_cyrus/server_gui/objs
debug: UI_DIR = $$PWD/../../debug_cyrus/server_gui/ui

TARGET = cyrus2015
#CONFIG   += console
#CONFIG   -= app_bundle

INCLUDEPATH += \
            $$PWD \
            /usr/local/include \
            ../TeamManager \
            ../shared \
            ../shared/utility \
            ../shared/proto \
            ../shared/tools \
            ../shared/tools/vartypes/vartypes \
            ../shared/tools/vartypes/vartypes/gui \
            ../shared/tools/vartypes/vartypes/primitives \
            ../shared/tools/vartypes/vartypes/xml


TEMPLATE = app

SOURCES += \
    transmitter/RobotSerialConnection.cpp \
    ai/SSLWorldModel.cpp \
    definition/SSLTeam.cpp \
    definition/SSLRobot.cpp \
    definition/SSLBall.cpp \
    ai/SSLGame.cpp \
    transmitter/RobotCommandPacket.cpp \
    ../shared/tools/serialib/serialib.cpp \
    ../shared/tools/socket/netraw.cpp \
    ../shared/utility/vector3d.cpp \
    ../shared/utility/vector2d.cpp \
    ai/SSLAnalyzer.cpp \
    soccer/sslagent.cpp \
    soccer/sslstrategy.cpp \
    transmitter/grsimsender.cpp \    
    transmitter/commandtransmitter.cpp \
    referee/SSLReferee.cpp \    
    controller/pidcontroller.cpp \    
    soccer/sslstrategymanager.cpp \
    soccer/sslrolemanager.cpp \
    soccer/sslrole.cpp \
    soccer/roles/waitrebound.cpp \
    soccer/roles/waitpass.cpp \
#    soccer/roles/positionrole.cpp \
    soccer/roles/opponentmarker.cpp \
    soccer/roles/goalkeeper.cpp \
    soccer/roles/defender.cpp \
    soccer/roles/blocker.cpp \
    soccer/roles/activerole.cpp \
    ../shared/proto/grsim/cpp/grsim_Replacement.pb.cc \
    ../shared/proto/grsim/cpp/grsim_Packet.pb.cc \
    ../shared/proto/grsim/cpp/grsim_Commands.pb.cc \
    ../shared/proto/referee/cpp/referee.pb.cc \
    ../shared/proto/vision/cpp/messages_robocup_ssl_wrapper.pb.cc \
    ../shared/proto/vision/cpp/messages_robocup_ssl_refbox_log.pb.cc \
    ../shared/proto/vision/cpp/messages_robocup_ssl_geometry.pb.cc \
    ../shared/proto/vision/cpp/messages_robocup_ssl_detection.pb.cc \
    ../shared/proto/visualizer/cpp/ssl_world.pb.cc \
    ../shared/proto/visualizer/cpp/ssl_visualizer.pb.cc \
    ../shared/proto/visualizer/cpp/ssl_planner.pb.cc \
    ../shared/proto/visualizer/cpp/ssl_decision.pb.cc \
    ../shared/proto/visualizer/cpp/ssl_analyzer.pb.cc \
    paramater-manager/parametermanager.cpp \
    paramater-manager/iniparser.cpp \
    vision/alphabetafilter.cpp \
    vision/robocup_ssl_client.cpp \
    vision/sslframe.cpp \
    planner/planning/planningproblem.cpp \
    planner/planning/trajectory.cpp \
    planner/planning/station.cpp \
    planner/planning/goalstate.cpp \
    planner/planning/planningagent.cpp \
    planner/planning/motionplan.cpp \
    planner/planning/obstacle.cpp \
    planner/planning/fieldbound.cpp \
    planner/planning/dynamicobstacle.cpp \
    ../shared/utility/ellipse.cpp \
    ../shared/utility/shape.cpp \
    soccer/sslgamepositions.cpp \
    soccer/sslskill.cpp \
    test/testvisioninput.cpp \
    test/testreferee.cpp \
    ../shared/utility/linesegment.cpp \
    debug-tools/logger.cpp \
    debug-tools/networkplotter.cpp \
    ../shared/proto/plotter/cpp/message_plotter.pb.cc \
    test/testskills.cpp \
    soccer/roles/sidecleaner.cpp \
    ../shared/utility/randomsampling.cpp \
    ../shared/utility/generalmath.cpp \
    planner/planning/sslplanningagent.cpp \
    planner/planning/spatialtree.cpp \
    planner/planning/rectangularfieldbound.cpp \
    ../shared/tools/vartypes/vartypes/VarXML.cpp \
    ../shared/tools/vartypes/vartypes/VarTypesInstance.cpp \
    ../shared/tools/vartypes/vartypes/VarTypesFactory.cpp \
    ../shared/tools/vartypes/vartypes/VarTypesBase.cpp \
    ../shared/tools/vartypes/vartypes/VarTypes.cpp \
    ../shared/tools/vartypes/vartypes/VarNotifier.cpp \
    ../shared/tools/vartypes/vartypes/VarBase64.cpp \
    ../shared/tools/vartypes/vartypes/gui/VarTreeViewOptions.cpp \
    ../shared/tools/vartypes/vartypes/gui/VarTreeView.cpp \
    ../shared/tools/vartypes/vartypes/gui/VarTreeModel.cpp \
    ../shared/tools/vartypes/vartypes/gui/VarItemDelegate.cpp \
    ../shared/tools/vartypes/vartypes/gui/VarItem.cpp \
    ../shared/tools/vartypes/vartypes/primitives/VarVal.cpp \
    ../shared/tools/vartypes/vartypes/primitives/VarType.cpp \
    ../shared/tools/vartypes/vartypes/primitives/VarTrigger.cpp \
    ../shared/tools/vartypes/vartypes/primitives/VarStringVal.cpp \
    ../shared/tools/vartypes/vartypes/primitives/VarStringEnum.cpp \
    ../shared/tools/vartypes/vartypes/primitives/VarString.cpp \
    ../shared/tools/vartypes/vartypes/primitives/VarShortVal.cpp \
    ../shared/tools/vartypes/vartypes/primitives/VarShort.cpp \
    ../shared/tools/vartypes/vartypes/primitives/VarSelection.cpp \
    ../shared/tools/vartypes/vartypes/primitives/VarQWidget.cpp \
    ../shared/tools/vartypes/vartypes/primitives/VarProtoBufferVal.cpp \
    ../shared/tools/vartypes/vartypes/primitives/VarProtoBuffer.cpp \
    ../shared/tools/vartypes/vartypes/primitives/VarList.cpp \
    ../shared/tools/vartypes/vartypes/primitives/VarIntVal.cpp \
    ../shared/tools/vartypes/vartypes/primitives/VarInt.cpp \
    ../shared/tools/vartypes/vartypes/primitives/VarExternal.cpp \
    ../shared/tools/vartypes/vartypes/primitives/VarDoubleVal.cpp \
    ../shared/tools/vartypes/vartypes/primitives/VarDouble.cpp \
    ../shared/tools/vartypes/vartypes/primitives/VarBoolVal.cpp \
    ../shared/tools/vartypes/vartypes/primitives/VarBool.cpp \
    ../shared/tools/vartypes/vartypes/primitives/VarBlob.cpp \
    ../shared/tools/vartypes/vartypes/xml/xmlParser.cpp \
    ../shared/tools/kalman-cpp/kalman.cpp \
    vision/kalmanfilter.cpp \
    vision/robotkalmanfilter.cpp \
    vision/ballfilter.cpp \
    vision/visionfilter.cpp \
    vision/robotclusterfilter.cpp \
    vision/sslvision.cpp \
    vision/robotfilter.cpp \
    ../TeamManager/watchfieldgraphics.cpp \
    ../TeamManager/mainwindow.cpp \
    ../TeamManager/fieldgraphicsview.cpp \
    ../TeamManager/cyrusserverpackethandler.cpp \
    debug-tools/debugclient.cpp \
    main_gui.cpp \
    debug-tools/builtindebug.cpp \
    ../TeamManager/udpsocket.cpp \
    ../TeamManager/plot-manager/scatterplotwidget.cpp \
    ../TeamManager/plot-manager/qcustomplot.cpp \
    ../TeamManager/plot-manager/plotwidget.cpp \
    ../TeamManager/plot-manager/plotmanagerwidget.cpp \
    ../TeamManager/graphics/graphic_vec.cpp \
    ../TeamManager/graphics/graphic_plan.cpp \
    ../TeamManager/graphics/graphic_num.cpp \
    ../TeamManager/graphics/graphic_intersect.cpp \
    ../TeamManager/graphics/graphic_circle.cpp \
    ../TeamManager/graphics/graphic_bot.cpp \
    ../TeamManager/graphics/graphic_ball.cpp \
    ../TeamManager/graphics/graphic_arc.cpp \
    ../TeamManager/robotstate.cpp \
    ../TeamManager/messengerwidget.cpp \ 
    paramater-manager/lookuptableloader.cpp \
    paramater-manager/skillparameters.cpp \
    controller/prcontroller.cpp


HEADERS += \
    transmitter/RobotSerialConnection.h \
    ../shared/tools/serialib/serialib.h \
    ../shared/tools/socket/ippacket.h \
    ../shared/tools/ssllistener.h \
    ../shared/general.h \
    ai/SSLWorldModel.h \
    definition/SSLTeam.h \
    definition/SSLRobot.h \
    definition/SSLObject.h \
    definition/SSLBall.h \
    ai/SSLGame.h \
    transmitter/RobotCommandPacket.h \
    ../shared/utility/vector3d.h \
    ../shared/utility/vector2d.h \
    ../shared/tools/socket/netraw.h \
    ../shared/tools/util.h \
    ai/SSLAnalyzer.h \
    soccer/sslagent.h \
    soccer/sslstrategy.h \
    transmitter/grsimsender.h \
    transmitter/commandtransmitter.h \
    ../shared/utility/generalmath.h \
    referee/SSLReferee.h \
    soccer/sslstrategymanager.h \
    soccer/sslrole.h \
    soccer/sslrolemanager.h \
    soccer/roles/waitrebound.h \
    soccer/roles/waitpass.h \
#    soccer/roles/positionrole.h \
    soccer/roles/opponentmarker.h \
    soccer/roles/goalkeeper.h \
    soccer/roles/defender.h \
    soccer/roles/blocker.h \
    soccer/roles/activerole.h \
    controller/pidcontroller.h \    
    ../shared/proto/grsim/cpp/grsim_Replacement.pb.h \
    ../shared/proto/grsim/cpp/grsim_Packet.pb.h \
    ../shared/proto/grsim/cpp/grsim_Commands.pb.h \
    ../shared/proto/referee/cpp/referee.pb.h \
    ../shared/proto/vision/cpp/messages_robocup_ssl_wrapper.pb.h \
    ../shared/proto/vision/cpp/messages_robocup_ssl_refbox_log.pb.h \
    ../shared/proto/vision/cpp/messages_robocup_ssl_geometry.pb.h \
    ../shared/proto/vision/cpp/messages_robocup_ssl_detection.pb.h \
    ../shared/proto/visualizer/cpp/ssl_world.pb.h \
    ../shared/proto/visualizer/cpp/ssl_visualizer.pb.h \
    ../shared/proto/visualizer/cpp/ssl_planner.pb.h \
    ../shared/proto/visualizer/cpp/ssl_decision.pb.h \
    ../shared/proto/visualizer/cpp/ssl_analyzer.pb.h \
    iniparser/iniparser.h \
    iniparser/parametermanager.h \
    paramater-manager/parametermanager.h \
    paramater-manager/iniparser.h \
    vision/alphabetafilter.h \
    vision/robocup_ssl_client.h \
    ../shared/utility/linesegment.h \
    vision/sslframe.h \
    planner/planning/obstacle.h \
    planner/planning/planningproblem.h \
    planner/planning/fieldbound.h \
    planner/planning/station.h \
    planner/planning/trajectory.h \
    planner/planning/goalstate.h \
    planner/planning/motionplan.h \
    planner/planning/planningagent.h \
    planner/planning/dynamicobstacle.h \
    ../shared/utility/ellipse.h \
    ../shared/utility/shape.h \
    soccer/sslgamepositions.h \
    soccer/sslskill.h \
    test/testvisioninput.h \
    test/testreferee.h \
    test/testmathfunctions.h \
    debug-tools/logger.h \
    debug-tools/networkplotter.h \
    ../shared/proto/plotter/cpp/message_plotter.pb.h \
    test/testskills.h \
    soccer/roles/sidecleaner.h \
    ../shared/utility/randomsampling.h \
    ../shared/utility/util.h \
    planner/planning/sslplanningagent.h \
    planner/planning/spatialvertex.h \
    planner/planning/spatialtree.h \
    planner/planning/rectangularfieldbound.h \
    ../shared/tools/vartypes/vartypes/VarXML.h \
    ../shared/tools/vartypes/vartypes/VarTypesInstance.h \
    ../shared/tools/vartypes/vartypes/VarTypesFactory.h \
    ../shared/tools/vartypes/vartypes/VarTypesBase.h \
    ../shared/tools/vartypes/vartypes/VarTypes.h \
    ../shared/tools/vartypes/vartypes/VarNotifier.h \
    ../shared/tools/vartypes/vartypes/VarBase64.h \
    ../shared/tools/vartypes/vartypes/DllDefines.h \
    ../shared/tools/vartypes/vartypes/gui/VarTreeViewOptions.h \
    ../shared/tools/vartypes/vartypes/gui/VarTreeView.h \
    ../shared/tools/vartypes/vartypes/gui/VarTreeModel.h \
    ../shared/tools/vartypes/vartypes/gui/VarItemDelegate.h \
    ../shared/tools/vartypes/vartypes/gui/VarItem.h \
    ../shared/tools/vartypes/vartypes/primitives/VarVal.h \
    ../shared/tools/vartypes/vartypes/primitives/VarType.h \
    ../shared/tools/vartypes/vartypes/primitives/VarTrigger.h \
    ../shared/tools/vartypes/vartypes/primitives/VarStringVal.h \
    ../shared/tools/vartypes/vartypes/primitives/VarStringEnum.h \
    ../shared/tools/vartypes/vartypes/primitives/VarString.h \
    ../shared/tools/vartypes/vartypes/primitives/VarShortVal.h \
    ../shared/tools/vartypes/vartypes/primitives/VarShort.h \
    ../shared/tools/vartypes/vartypes/primitives/VarSelection.h \
    ../shared/tools/vartypes/vartypes/primitives/VarQWidget.h \
    ../shared/tools/vartypes/vartypes/primitives/VarProtoBufferVal.h \
    ../shared/tools/vartypes/vartypes/primitives/VarProtoBuffer.h \
    ../shared/tools/vartypes/vartypes/primitives/VarList.h \
    ../shared/tools/vartypes/vartypes/primitives/VarIntVal.h \
    ../shared/tools/vartypes/vartypes/primitives/VarInt.h \
    ../shared/tools/vartypes/vartypes/primitives/VarExternal.h \
    ../shared/tools/vartypes/vartypes/primitives/VarDoubleVal.h \
    ../shared/tools/vartypes/vartypes/primitives/VarDouble.h \
    ../shared/tools/vartypes/vartypes/primitives/VarBoolVal.h \
    ../shared/tools/vartypes/vartypes/primitives/VarBool.h \
    ../shared/tools/vartypes/vartypes/primitives/VarBlob.h \
    ../shared/tools/vartypes/vartypes/xml/xmlParser.h \
    ../shared/tools/kalman-cpp/kalman.hpp \
    vision/kalmanfilter.h \
    vision/robotkalmanfilter.h \
    vision/ballfilter.h \
    vision/visionfilter.h \
    vision/robotclusterfilter.h \
    vision/sslvision.h \
    vision/robotfilter.h \
    ../TeamManager/watchfieldgraphics.h \
    ../TeamManager/mainwindow.h \
    ../TeamManager/fieldgraphicsview.h \
    ../TeamManager/cyrusserverpackethandler.h \
    debug-tools/debugclient.h \
    debug-tools/builtindebug.h \
    ../TeamManager/udpsocket.h \
    ../TeamManager/plot-manager/scatterplotwidget.h \
    ../TeamManager/plot-manager/qcustomplot.h \
    ../TeamManager/plot-manager/plotwidget.h \
    ../TeamManager/plot-manager/plotmanagerwidget.h \
    ../TeamManager/graphics/graphic_vec.h \
    ../TeamManager/graphics/graphic_plan.h \
    ../TeamManager/graphics/graphic_num.h \
    ../TeamManager/graphics/graphic_intersect.h \
    ../TeamManager/graphics/graphic_circle.h \
    ../TeamManager/graphics/graphic_bot.h \
    ../TeamManager/graphics/graphic_ball.h \
    ../TeamManager/graphics/graphic_arc.h \
    ../TeamManager/robotstate.h \
    ../TeamManager/messengerwidget.h \
    paramater-manager/lookuptableloader.h \
    paramater-manager/skillparameters.h \
    controller/prcontroller.h


OTHER_FILES += \            
    ../shared/proto/referee/proto/*.proto \
    ../shared/proto/vision/proto/*.proto \
    ../shared/proto/visualizer/proto/*.proto \
    ../settings/*.json


FORMS += \
    ../TeamManager/watchfieldgraphics.ui \
    ../TeamManager/mainwindow.ui \
    ../TeamManager/plot-manager/scatterplotwidget.ui \
    ../TeamManager/plot-manager/plotwidget.ui \
    ../TeamManager/plot-manager/plotmanagerwidget.ui

RESOURCES += \
    ../TeamManager/icons.qrc

