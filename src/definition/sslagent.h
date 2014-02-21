#ifndef SSLAGENT_H
#define SSLAGENT_H

#include "definition/SSLRobot.h"
#include "soccer/roles/SSLRole.h"
#include "general.h"

#include "planner/planning/goalstate.h"
#include "planner/planning/planningproblem.h"

class SSLAgent
{
public:
    SSLAgent(SSL::Color color);
    ~SSLAgent();

    SSLRobot* robot;
    SSLRole* role;

    GoalState target;
    PlanningProblem planner;


    // SSLController controller;

    bool isNull();
    int getID() const;

    void run();
private:

    ObstacleSet myDynamicObstacleSet;
    ObstacleSet penaltyAreaObstacleSet;
};

#endif // SSLAGENT_H
