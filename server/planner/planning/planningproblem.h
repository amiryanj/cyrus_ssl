#ifndef PLANNINGPROBLEM_H
#define PLANNINGPROBLEM_H

#include <vector>
#include "station.h"
#include "goalstate.h"
#include "fieldbound.h"
#include "obstacle.h"
#include "randomtree.h"
#include "trajectory.h"
#include "planningagent.h"
#include "sslmath.h"
#include "motionplan.h"
#include "../../../common/math/ellipse.h"

#define MAX_TREE_SIZE 550
#define MAX_SAMPLING_TRY 10
#define MAX_STATION_CATCH_SIZE 50
#define MAX_RRT_STEP_TRY 1200
#define GOAL_PROB 0.25

using namespace DMP;

class PlanningChromosom;

class PlanningProblem
{
    enum ExtendResult {Trapped, Advanced, Reached};
public:
    PlanningProblem();

    // for singleton usages
    static PlanningProblem* instance;
    static PlanningProblem* getInstance();

    void setPlanningAgent(PlanningAgent ag);
    PlanningAgent getPlanningAgent() const;

    void computeCost(Trajectory &p);

    void setBound(FieldBound fb);
    FieldBound getBound() const;

    void setStaticObstacles(ObstacleSet st_obs);
    ObstacleSet getStaticObstacles() const;

    void setDynamicObstacles(ObstacleSet dy_obs);
    ObstacleSet getDynamicObstacles() const;

    void clearObstacles(bool dynamix = true, bool statix = true);

    void setInitialState(Station st);
    Station getInitialState() const;

    void setGoalPoint(Station st);
    void setGoalRegion(GoalState gl);
    GoalState getGoal();

    void setPenaltyWeights(Trajectory::PlanCost cost_weights);
    Trajectory::PlanCost getPenaltyWeights() const;

    RandomTree &getTree();
    Trajectory getTrajectory() const;
    Velocity getControl(uint i = 0);
    Velocity getNextControl(Trajectory tr_);
    Trajectory getPlan();

    Station getFirstSubGoal();

    // each of this planners manipulate tree, trajec, planningResult, planningTime
    bool solve();
    bool testFunc();


    void deactive();
    Trajectory RRTsolve(float arg1);
    Trajectory ERRTsolve();
    Trajectory GRRTsolve();
    Trajectory RRTConnectSolve(double arg1);
    Trajectory PruneTrajectory(Trajectory& input_plan, const ObstacleSet &ob_set);

    Trajectory PotentialFieldSolve(const ObstacleSet& ob_set);
    Trajectory RRT_APF_Solve(Trajectory& rrt_plan_, const ObstacleSet& ob_set, PlanningChromosom &params);

    vector<Vector2D> ObstacleForces(const Station &st, const ObstacleSet &ob_set);
    Vector2D RRTDirectedForce(const Station& st, Trajectory& rrt_);
    Vector2D GoalAttractiveForce(const Station& st);


    bool planningResult;
    double planningTime;

    float distToObstacle(Station A, const Obstacle& ob, b2Vec2 &A_point, b2Vec2 &ob_point);

    RandomTree backward_tree; // backward_tree for rrt-connect algorithm
    double search_diameter;

private:
    Station initialState;
    GoalState goal;

    PlanningAgent agent;
    FieldBound actualBound;
    FieldBound temporalBound;
    ObstacleSet stat_obstacles;
    ObstacleSet dyna_obstacles;

    RandomTree tree;

    Trajectory trajec;

    Trajectory bestPlan;

    Station SampleState();
    Station SampleStateUniform();
    Station SampleStateInEllipse(const Ellipse &ell_);
    Station GaussinaStateSample(Station mean, double var);

    Velocity UniformControlSample();

    bool CheckValidity(Station A);
    bool hasCollision(Station &st, const ObstacleSet& ob_set);
    bool hasCollision(Station &st, const Obstacle& ob);

    bool pathHasCollision(Station &from, Station &to, const ObstacleSet& ob_set);
    bool pathHasCollision(Station &from, Station &to, const Obstacle &ob);

    Obstacle* nearestObstacle(Station A, const ObstacleSet& obset, float &dist, b2Vec2 &A_point, b2Vec2 &ob_point);

    Station RRTExtend(const Station &start, const Station &target, float extension_len);
    ExtendResult RRTStep(RandomTree &tree, float extension_len);
    Trajectory buildTrajectoryFromTree();
    void buildVelocityProfile();
    void solveInvalidInitialState();
    void solveInvalidGoalState();
//    bool isGoalStateValid();
    b2Transform identity_trans;
    void testCollisionFunc();

public:
    bool checkPlanValidity(Trajectory &plan, float tolerance_coeff = 1.5);
//    float EucleadianDistance(const Station& A, const Station& B);




};

#endif // PLANNINGPROBLEM_H
