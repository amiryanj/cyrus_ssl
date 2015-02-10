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
    SSLAgent();
    ~SSLAgent();

    SSLRobot* robot;
    SSLRole* role;

    Vector3D tempTarget;
    PlanningProblem planner;
    PIDController controller;

    Vector3D desiredGlobalSpeed;
    Vector3D appliedGlobalSpeed;
    Vector3D appliedLocalSpeed;

    string skill_in_use; // for visualizer use

    // SSLController controller;

    bool isNull();
    int getID() const;

    void run();

private:
};

#endif // _SSLAGENT_H