#-------------------------------------------------
#
# Project created by QtCreator 2013-11-29T17:10:55
#
#-------------------------------------------------

LIBS += -lBox2D -lboost_system
INCLUDEPATH += $$PWD

SOURCES += $$PWD/obstacle.cpp \
    $$PWD/rrtvertex.cpp \
    $$PWD/randomtree.cpp \
    $$PWD/trajectory.cpp \
    $$PWD/planningproblem.cpp \
    $$PWD/goalstate.cpp \
    $$PWD/station.cpp \
    $$PWD/fieldbound.cpp \
    $$PWD/dynamicobstacle.cpp \
    $$PWD/velocity.cpp \
    $$PWD/planningagent.cpp \
    $$PWD/plannermath.cpp

HEADERS  += obstacle.h \
    rrtvertex.h \
    randomtree.h \
    trajectory.h \
    planningproblem.h \
    goalstate.h \
    station.h \
    fieldbound.h \
    dynamicobstacle.h \
    velocity.h \
    planningagent.h \
    plannermath.h
    
