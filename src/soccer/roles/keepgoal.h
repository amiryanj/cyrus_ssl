#ifndef KEEPGOAL_H
#define KEEPGOAL_H

#include "SSLRole.h"

class KeepGoal : public SSLRole
{
public:
    KeepGoal(SSLRobot*);

    Planner::State* run();

};

#endif // KEEPGOAL_H
