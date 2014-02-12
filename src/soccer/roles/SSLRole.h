#ifndef SSLROLE_H
#define SSLROLE_H

#include "../definition/SSLRobot.h"
#include "planner/planning/goalstate.h"

class SSLRole
{
public:
    enum ActiveT{Active, NonActive};
    SSLRole(SSLRobot*);
    ~SSLRole();

    virtual GoalState run() = 0;

    ActiveT activeType;

    SSLRobot* getRobot();
    GoalState getTarget();

private:

    SSLRobot* robot;

};

#endif // SSLROLE_H
