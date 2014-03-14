#ifndef SSLAGENT_H
#define SSLAGENT_H

#include "../definition/SSLRobot.h"
#include "../soccer/roles/SSLRole.h"
#include "../general.h"

#include "../planner/planning/goalstate.h"
#include "../planner/planning/planningproblem.h"
#include "../controller/pidcontroller.h"

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

    Vector3D temp_desired_vel;
    Vector3D temp_applied_vel_global;
    Vector3D temp_applied_vel_local;


    // SSLController controller;

    bool isNull();
    int getID() const;

    void run();
private:
    ObstacleSet allRobotsObs;
    Obstacle* ballOb;
    ObstacleSet myDynamicObstacleSet;
    ObstacleSet penaltyAreaObs;
};

#endif // SSLAGENT_H
