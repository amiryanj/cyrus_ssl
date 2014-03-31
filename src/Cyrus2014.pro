#-------------------------------------------------
#
# Project created by QtCreator 2013-09-06T18:59:38
#
#-------------------------------------------------

#QT       += core
#QT       -= gui

LIBS += -lprotobuf -lboost_system -lBox2D

TARGET = Cyrus2014
#CONFIG   += console
#CONFIG   -= app_bundle

INCLUDEPATH += \
            $$PWD \
            thirdparty\
            thirdparty/socket \
            tools

TEMPLATE = app

SOURCES += \
    main.cpp \
    vision/SSLVision.cpp \    
    transmitter/RobotSerialConnection.cpp \
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
    transmitter/RobotCommandPacket.cpp \
    vision/SSLRobotKalmanFilter.cpp \
    tools/vector3d.cpp \
    tools/vector2d.cpp \
    vision/frame.cpp \
    vision/VisionFilterModule.cpp \
    thirdparty/socket/netraw.cpp \
    ai/SSLAnalyzer.cpp \
    vision/SSLBallKalmanFilter.cpp \
    definition/sslagent.cpp \
    definition/sslstrategy.cpp \
    tools/stdlist.cpp \
    gui/guihandler.cpp \
    gui/cpp/ssl_visualizer.pb.cc \
    gui/cpp/ssl_world.pb.cc \
    gui/cpp/ssl_decision.pb.cc \
    gui/cpp/ssl_planner.pb.cc \
    gui/cpp/ssl_analyzer.pb.cc \
    transmitter/grsimsender.cpp \
    transmitter/grSim/cpp/grSim_Replacement.pb.cc \
    transmitter/grSim/cpp/grSim_Packet.pb.cc \
    transmitter/grSim/cpp/grSim_Commands.pb.cc \
    transmitter/commandtransmitter.cpp \
    tools/sslmath.cpp \
    vision/naivekalmanfilter.cpp \
    referee/SSLReferee.cpp \
    referee/referee/cpp/referee.pb.cc \
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
    soccer/roles/wallstander.cpp \
    soccer/roles/waitrebound.cpp \
    soccer/roles/waitpass.cpp \
    soccer/roles/positionrole.cpp \
    soccer/roles/playstarter.cpp \
    soccer/roles/opponentmarker.cpp \
    soccer/roles/goalkeeper.cpp \
    soccer/roles/defender.cpp \
    soccer/roles/blocker.cpp \
    soccer/roles/activerole.cpp

HEADERS += \
    vision/SSLVision.h \
    transmitter/RobotSerialConnection.h \
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
    transmitter/RobotCommandPacket.h \
    vision/SSLRobotKalmanFilter.h \
    tools/vector3d.h \
    tools/vector2d.h \
    vision/frame.h \
    vision/VisionFilterModule.h \
    thirdparty/socket/netraw.h \
    thirdparty/util.h \
    ai/SSLAnalyzer.h \
    vision/SSLBallKalmanFilter.h \
    definition/sslagent.h \
    definition/sslstrategy.h \
    tools/stdlist.h \
    gui/guihandler.h \
    gui/cpp/ssl_visualizer.pb.h \
    gui/cpp/ssl_world.pb.h \
    gui/cpp/ssl_decision.pb.h \
    gui/cpp/ssl_planner.pb.h \
    gui/cpp/ssl_analyzer.pb.h \
    transmitter/grsimsender.h \
    transmitter/grSim/cpp/grSim_Replacement.pb.h \
    transmitter/grSim/cpp/grSim_Packet.pb.h \
    transmitter/grSim/cpp/grSim_Commands.pb.h \
    transmitter/commandtransmitter.h \
    tools/sslmath.h \
    vision/naivekalmanfilter.h \
    referee/SSLReferee.h \
    referee/referee/cpp/referee.pb.h \
    soccer/SSLSkill.h \
    soccer/sslstrategymanager.h \
    soccer/roles/sslrole.h \
    soccer/sslrolemanager.h \
    soccer/roles/wallstander.h \
    soccer/roles/waitrebound.h \
    soccer/roles/waitpass.h \
    soccer/roles/positionrole.h \
    soccer/roles/playstarter.h \
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
    planner/planning/dynamicobstacle.h

OTHER_FILES += \
    todo.txt \
    planner/planning/Planner.pri \
    referee/referee/referee.proto \
    /etc/sslrefbox/referee.conf \
    gui/proto/ssl_world.proto \
    gui/proto/ssl_visualizer.proto \
    gui/proto/ssl_planner.proto \
    gui/proto/ssl_decision.proto \
    gui/proto/ssl_analyzer.proto


