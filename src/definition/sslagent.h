#ifndef _SSLAGENT_H
#define _SSLAGENT_H

#include "../definition/SSLRobot.h"
#include "../general.h"

#include "../planner/planning/goalstate.h"
#include "../planner/planning/planningproblem.h"
#include "../controller/pidcontroller.h"

class SSLRole;

class SSLAgent
{
public:
    SSLAgent(SSL::Color our_color, SSL::Side our_side);
    ~SSLAgent();

    SSLRobot* robot;
    SSLRole* role;

    GoalState target;
    PlanningProblem planner;
    PIDController controller;

    Vector3D desiredGlobalSpeed;
    Vector3D appliedGlobalSpeed;
    Vector3D appliedLocalSpeed;


    // SSLController controller;

    bool isNull();
    int getID() const;

    void run();

private:
};

#endif // _SSLAGENT_H
