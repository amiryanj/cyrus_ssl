#ifndef SSLROLE_H
#define SSLROLE_H

#include "../planning/rrtplanner.h"
#include "../definition/SSLRobot.h"

class SSLRole
{
public:
    enum ActiveT{Active, NonActive};
    SSLRole(SSLRobot*);
    ~SSLRole();

    virtual Planner::State* run() = 0;

    ActiveT activeType;

    SSLRobot* getRobot();
    Planner::State* getTarget();

private:

    SSLRobot* robot;
    const Planner::State* target;

};

#endif // SSLROLE_H
