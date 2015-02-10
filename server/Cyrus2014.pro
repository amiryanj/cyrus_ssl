#-------------------------------------------------
#
# Project created by QtCreator 2013-09-06T18:59:38
#
#-------------------------------------------------

#QT       += core network
#QT       -= gui

LIBS += -lprotobuf -lboost_system -lBox2D

DEFINES += _USE_BOX2D_

TARGET = Cyrus2014
#CONFIG   += console
#CONFIG   -= app_bundle

INCLUDEPATH += \
            $$PWD \
            /usr/local/include \
            ../common \
            ../common/math \
            ../common/tools \
            ../common/protoc \
            ../common/thirdparty \
            ../common/thirdparty/socket \
            tools

TEMPLATE = app

SOURCES += \
    main.cpp \
    vision/SSLVision.cpp \    
    transmitter/RobotSerialConnection.cpp \
    ../common/thirdparty/serialib/serialib.cpp \
    ../common/thirdparty/socket/IPPacket.cpp \
    ../common/tools/SSLListener.cpp \
#    tools/SSLException.cpp \
    ai/SSLWorldModel.cpp \
    definition/SSLTeam.cpp \
    definition/SSLRobot.cpp \
    definition/SSLObject.cpp \
    definition/SSLBall.cpp \
    definition/SSLRobotPhysic.cpp \
    ai/SSLGame.cpp \
    transmitter/RobotCommandPacket.cpp \
    ../common/math/vector3d.cpp \
    ../common/math/vector2d.cpp \
    ../common/thirdparty/socket/netraw.cpp \
    ai/SSLAnalyzer.cpp \
    definition/sslagent.cpp \
    definition/sslstrategy.cpp \
    gui/guihandler.cpp \    
    transmitter/grsimsender.cpp \    
    transmitter/commandtransmitter.cpp \
    ../common/math/sslmath.cpp \
    referee/SSLReferee.cpp \    
    controller/pidcontroller.cpp \
    planner/planning/velocity.cpp \
    planner/planning/trajectory.cpp \
    planner/planning/station.cpp \
    planner/planning/rrtvertex.cpp \
    planner/planning/randomtree.cpp \
    planner/planning/planningproblem.cpp \
    planner/planning/planningagent.cpp \
    planner/planning/plannermath.cpp \
    planner/planning/obstacle.cpp \
    planner/planning/goalstate.cpp \
    planner/planning/fieldbound.cpp \
    planner/planning/dynamicobstacle.cpp \
    soccer/sslstrategymanager.cpp \
    soccer/SSLSkill.cpp \
    soccer/sslrolemanager.cpp \
    soccer/roles/sslrole.cpp \
    soccer/roles/waitrebound.cpp \
    soccer/roles/waitpass.cpp \
    soccer/roles/positionrole.cpp \
    soccer/roles/opponentmarker.cpp \
    soccer/roles/goalkeeper.cpp \
    soccer/roles/defender.cpp \
    soccer/roles/blocker.cpp \
    soccer/roles/activerole.cpp \
    vision/VisionFilter.cpp \
    vision/NaiveKalman.cpp \
    vision/BallFilter.cpp \
    vision/RobotFilter.cpp \
    vision/Frame.cpp \
    ../common/protoc/grSim/cpp/grSim_Replacement.pb.cc \
    ../common/protoc/grSim/cpp/grSim_Packet.pb.cc \
    ../common/protoc/grSim/cpp/grSim_Commands.pb.cc \
    ../common/protoc/referee/cpp/referee.pb.cc \
    ../common/protoc/vision/cpp/messages_robocup_ssl_wrapper.pb.cc \
    ../common/protoc/vision/cpp/messages_robocup_ssl_refbox_log.pb.cc \
    ../common/protoc/vision/cpp/messages_robocup_ssl_geometry.pb.cc \
    ../common/protoc/vision/cpp/messages_robocup_ssl_detection.pb.cc \
    ../common/protoc/visualizer/cpp/ssl_world.pb.cc \
    ../common/protoc/visualizer/cpp/ssl_visualizer.pb.cc \
    ../common/protoc/visualizer/cpp/ssl_planner.pb.cc \
    ../common/protoc/visualizer/cpp/ssl_decision.pb.cc \
    ../common/protoc/visualizer/cpp/ssl_analyzer.pb.cc

HEADERS += \
    vision/SSLVision.h \
    transmitter/RobotSerialConnection.h \
    ../common/thirdparty/serialib/serialib.h \
    ../common/thirdparty/socket/IPPacket.h \
    ../common/tools/SSLListener.h \
#    tools/SSLException.h \
    ../common/general.h \
    ai/SSLWorldModel.h \
    definition/SSLTeam.h \
    definition/SSLRobot.h \
    definition/SSLObject.h \
    definition/SSLBall.h \
    definition/SSLRobotPhysic.h \
    definition/Concepts.h \
    ai/SSLGame.h \
    transmitter/RobotCommandPacket.h \
    ../common/math/vector3d.h \
    ../common/math/vector2d.h \
    ../common/thirdparty/socket/netraw.h \
    ../common/thirdparty/util.h \
    ai/SSLAnalyzer.h \
    definition/sslagent.h \
    definition/sslstrategy.h \
    gui/guihandler.h \
    transmitter/grsimsender.h \
    transmitter/commandtransmitter.h \
    ../common/math/sslmath.h \
    referee/SSLReferee.h \
    soccer/SSLSkill.h \
    soccer/sslstrategymanager.h \
    soccer/roles/sslrole.h \
    soccer/sslrolemanager.h \
    soccer/roles/waitrebound.h \
    soccer/roles/waitpass.h \
    soccer/roles/positionrole.h \
    soccer/roles/opponentmarker.h \
    soccer/roles/goalkeeper.h \
    soccer/roles/defender.h \
    soccer/roles/blocker.h \
    soccer/roles/activerole.h \
    controller/pidcontroller.h \
    planner/planning/velocity.h \
    planner/planning/trajectory.h \
    planner/planning/station.h \
    planner/planning/rrtvertex.h \
    planner/planning/randomtree.h \
    planner/planning/planningproblem.h \
    planner/planning/planningagent.h \
    planner/planning/plannermath.h \
    planner/planning/obstacle.h \
    planner/planning/goalstate.h \
    planner/planning/fieldbound.h \
    planner/planning/dynamicobstacle.h \
    vision/VisionFilter.h \
    vision/RobotFilter.h \
    vision/BallFilter.h \
    vision/NaiveKalman.h \
    vision/Frame.h \
    ../common/protoc/grSim/cpp/grSim_Replacement.pb.h \
    ../common/protoc/grSim/cpp/grSim_Packet.pb.h \
    ../common/protoc/grSim/cpp/grSim_Commands.pb.h \
    ../common/protoc/referee/cpp/referee.pb.h \
    ../common/protoc/vision/cpp/messages_robocup_ssl_wrapper.pb.h \
    ../common/protoc/vision/cpp/messages_robocup_ssl_refbox_log.pb.h \
    ../common/protoc/vision/cpp/messages_robocup_ssl_geometry.pb.h \
    ../common/protoc/vision/cpp/messages_robocup_ssl_detection.pb.h \
    ../common/protoc/visualizer/cpp/ssl_world.pb.h \
    ../common/protoc/visualizer/cpp/ssl_visualizer.pb.h \
    ../common/protoc/visualizer/cpp/ssl_planner.pb.h \
    ../common/protoc/visualizer/cpp/ssl_decision.pb.h \
    ../common/protoc/visualizer/cpp/ssl_analyzer.pb.h

OTHER_FILES += \
    todo.txt \
    planner/planning/Planner.pri \
    /etc/sslrefbox/referee.conf \
    ../common/protoc/referee/referee.proto \
    ../common/protoc/referee/compile.sh \
    ../common/protoc/vision/proto/messages_robocup_ssl_wrapper.proto \
    ../common/protoc/vision/proto/messages_robocup_ssl_refbox_log.proto \
    ../common/protoc/vision/proto/messages_robocup_ssl_geometry.proto \
    ../common/protoc/vision/proto/messages_robocup_ssl_detection.proto \
    ../common/protoc/vision/proto/compile.sh \
    ../common/protoc/visualizer/proto/ssl_world.proto \
    ../common/protoc/visualizer/proto/ssl_visualizer.proto \
    ../common/protoc/visualizer/proto/ssl_planner.proto \
    ../common/protoc/visualizer/proto/ssl_decision.proto \
    ../common/protoc/visualizer/proto/ssl_analyzer.proto \
    ../common/protoc/visualizer/proto/compile.sh
