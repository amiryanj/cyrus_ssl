#-------------------------------------------------
#
# Project created by QtCreator 2013-09-06T18:59:38
#
#-------------------------------------------------

#QT       += core network
#QT       -= gui

LIBS += -lprotobuf -lboost_system -lboost_filesystem -lBox2D

DEFINES += _USE_BOX2D_

release: DESTDIR = $$PWD/../../release_cyrus/server
release: MOC_DIR = $$PWD/../../release_cyrus/server/mocs
release: OBJECTS_DIR = $$PWD/../../release_cyrus/server/objs

debug: DESTDIR = $$PWD/../../debug_cyrus/server
debug: MOC_DIR = $$PWD/../../debug_cyrus/server/mocs
debug: OBJECTS_DIR = $$PWD/../../debug_cyrus/server/objs

TARGET = cyrus2014
#CONFIG   += console
#CONFIG   -= app_bundle

INCLUDEPATH += \
            $$PWD \
            /usr/local/include \
            ../shared \
            ../shared/utility \
            ../shared/proto \
            ../shared/tools


TEMPLATE = app

SOURCES += \
    main.cpp \
    vision/SSLVision.cpp \    
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
    gui/guihandler.cpp \    
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
    vision/VisionFilter.cpp \
    vision/NaiveKalman.cpp \
    vision/BallFilter.cpp \
    vision/RobotFilter.cpp \
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
    log-tools/logger.cpp \
    log-tools/networkplotter.cpp \
    ../shared/proto/plotter/cpp/message_plotter.pb.cc \
    test/testskills.cpp \
    soccer/roles/sidecleaner.cpp \
    ../shared/utility/randomsampling.cpp \
    ../shared/utility/generalmath.cpp \
    planner/planning/sslplanningagent.cpp \
    planner/planning/spatialtree.cpp \
    planner/planning/rectangularfieldbound.cpp

HEADERS += \
    vision/SSLVision.h \
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
    gui/guihandler.h \
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
    vision/VisionFilter.h \
    vision/RobotFilter.h \
    vision/BallFilter.h \
    vision/NaiveKalman.h \
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
    log-tools/logger.h \
    log-tools/networkplotter.h \
    ../shared/proto/plotter/cpp/message_plotter.pb.h \
    test/testskills.h \
    soccer/roles/sidecleaner.h \
    ../shared/utility/randomsampling.h \
    ../shared/utility/util.h \
    planner/planning/sslplanningagent.h \
    planner/planning/spatialvertex.h \
    planner/planning/spatialtree.h \
    planner/planning/rectangularfieldbound.h

OTHER_FILES += \            
    ../shared/proto/referee/proto/*.proto \
    ../shared/proto/vision/proto/*.proto \
    ../shared/proto/visualizer/proto/*.proto \
    ../settings/*.json

