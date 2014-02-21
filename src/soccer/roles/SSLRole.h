#ifndef SSLROLE_H
#define SSLROLE_H

#include "../../definition/SSLRobot.h"
#include "../../planner/planning/goalstate.h"

class SSLRole
{
public:
    enum RoleType {ROLE_UNKNOWN, ROLE_GOALIE, ROLE_DEFENDER, ROLE_BLOCKER, ROLE_MARKER, ROLE_PLAYMAKER};

    SSLRole(SSLRobot*);
    virtual ~SSLRole();

    virtual GoalState run() = 0;

    RoleType type;
    bool isActive;

    SSLRobot* getRobot();
    GoalState getTarget();

private:
    SSLRobot* robot; // robot assigned to
    GoalState target;
};

#endif // SSLROLE_H
