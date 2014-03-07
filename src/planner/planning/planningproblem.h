#ifndef PLANNINGPROBLEM_H
#define PLANNINGPROBLEM_H

#include <vector>
#include "station.h"
#include "goalstate.h"
#include "fieldbound.h"
#include "obstacle.h"
#include "velocity.h"
#include "randomtree.h"
#include "trajectory.h"
#include "planningagent.h"
#include <iostream>

#define MAX_TREE_SIZE 300
#define MAX_SAMPLING_TRY 10
#define MAX_STATION_CATCH_SIZE 50
#define MAX_RRT_STEP_TRY 400
#define GOAL_PROB 0.5
#define STEP 0.01f

class PlanningProblem        
{
    enum ExtendResult {Trapped, Advanced, Reached};
public:
    PlanningProblem();

    void setPlanningAgent(PlanningAgent ag);
    PlanningAgent getPlanningAgent() const;

    void setBound(FieldBound bn);
    FieldBound getBound() const;

    void setStaticObstacles(ObstacleSet st_obs);
    ObstacleSet getStaticObstacles() const;
    void setDynamicObstacles(ObstacleSet dy_obs);
    void clearObstacles();

    void setInitialState(Station st);
    Station getInitialState() const;

    void setGoalPoint(Station st);
    void setGoalRegion(GoalState gl);
    GoalState getGoal();

    RandomTree getTree() const;
    Trajectory getTrajectory() const;
    Velocity getControl(unsigned int i = 0);

    // each of this planners manipulate tree, trajec, planningResult, planningTime
    void RRTsolve();
    void ERRTsolve();
    void GRRTsolve();

    void PotentialFieldSolve();

    bool planningResult;
    double planningTime;

private:
    Station initialState;
    GoalState goal;

    PlanningAgent agent;
    FieldBound bound;
    ObstacleSet stat_obstacles;
    ObstacleSet dyna_obstacles;

    RandomTree tree;

    Trajectory trajec;

    Station SampleStateUniform();
    Station GaussinaStateSample(Station mean, double var);

    Velocity UniformControlSample();

    bool CheckValidity(Station &A);
    bool hasCollision(Station &st, const ObstacleSet& ob_set);
    bool hasCollision(Station &st, const Obstacle& ob);

    Station RRTExtend(const Station &start, const Station &target);
    ExtendResult RRTStep();
    void buildTrajectory();

    double EucleadianDistance(const Station& A, const Station& B);

    void testCollisionFunc();


};

#endif // PLANNINGPROBLEM_H
