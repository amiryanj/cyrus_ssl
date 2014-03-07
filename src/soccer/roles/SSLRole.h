#ifndef SSLROLE_H
#define SSLROLE_H

#include "../../definition/SSLRobot.h"
#include "../../planner/planning/goalstate.h"

class SSLRole
{
public:
    enum RoleType {ROLE_UNKNOWN, GoalKeeper, ROLE_DEFENDER, ROLE_BLOCKER, ROLE_MARKER, ROLE_PLAYMAKER};

    SSLRole();
    virtual ~SSLRole();

    virtual GoalState run() = 0;

    RoleType type;
    bool isActive;

    SSLRobot* getRobot();
    void setRobot(SSLRobot* r);
    GoalState getTarget();

protected:
    SSLRobot* robot; // robot assigned to
    GoalState target;
};

#endif // SSLROLE_H
