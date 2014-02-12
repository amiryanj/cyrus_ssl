#ifndef SSLAGENT_H
#define SSLAGENT_H

#include "definition/SSLRobot.h"
#include "soccer/roles/SSLRole.h"
#include "general.h"

#include "planner/planning/goalstate.h"
#include "planner/planning/planningproblem.h"
//typedef Planner::State GoalState;
//typedef Planner::RRTPlanner Planner;

class SSLAgent
{
public:
    SSLAgent();
    ~SSLAgent();

    SSLRobot* realRobot;
    SSLRole* role;

    GoalState target;
    PlanningProblem planner;


    bool isNull();
    int getID() const;

    void run();


private:
};

#endif // SSLAGENT_H
