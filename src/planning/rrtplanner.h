#ifndef RRTPLANNER_H
#define RRTPLANNER_H

#include <vector>
#include <iostream>
#include <../tools/vector2d.h>
#include <../tools/vector3d.h> // x, y, teta
#include "obstacle.h"

//#include <general.h>

#include <boost/date_time/posix_time/posix_time.hpp>
using namespace boost::posix_time;

#define MAX_TREE_NODE 300
#define MAX_EXTENSION_TRY 1500


using namespace std;

namespace Planning{

typedef Vector3D MPState;
typedef vector<MPState> MPPlan;

class PlannerAgentShape
{

public:
    PlannerAgentShape(b2Shape::Type type = b2Shape::e_circle);

    b2Shape *shape;

    double max_vel;
    double max_rot; // radian
    double mass;
    MPState init_position;

    PlannerAgentShape& operator=(const PlannerAgentShape& other);

private:
};

class PlannerBound
{
public:
    PlannerBound();
    PlannerBound(double left,  double down, double right, double top);
    void set(double left, double down, double right, double top);
    void set(Vector2D downLeft, Vector2D topRight);

    bool isEmpty();

    Vector2D getTopLeft();
    Vector2D getTopRight();
    Vector2D getDownLeft();
    Vector2D getDownRight();

    double topBound;
    double downBound;
    double rightBound;
    double leftBound;
};

class RRTPlanner
    {
    struct TreeNode {
        TreeNode() {}
        TreeNode(MPState st_,int index_, int father_ind, int depth_){
            state = st_;
            index = index_;
            fatherIndex = father_ind;
            depth = depth_;
        }
        bool operator ==(TreeNode other){
            return (this->index == other.index);
        }
        TreeNode& operator = (TreeNode other){
            state = other.state;
            index = other.index;
            fatherIndex = other.fatherIndex;
            depth = other.depth;
            return *this;
        }
        int index;
        int fatherIndex;
        unsigned int depth;
        MPState state;
    };

    typedef vector<TreeNode> RRT_Tree;

    public:
        RRTPlanner();
//        typedef vector<Obstacle> ObstacleSet;

        RRT_Tree rrtTree;

        MPState initial;
        MPState goal;
        PlannerBound bound;
        vector<Obstacle> obstacleList;

        PlannerAgentShape agent;
        vector<MPState> wayPoints;

        double planningTime;
        bool plannerSucceed;

        // ********** methods ***************************
        void setInitial(const MPState &initialState);
        void setBound(const PlannerBound b);
        void setAgent(const PlannerAgentShape &ag);
        void setGoalState(const MPState &g);

        Obstacle generateRandObstacle();

        void plan();
        void greedyPlan();

        MPPlan getPlan();

        // time measurement
        double getCurrentTimeMiliSec();

    private:
        double dist(const MPState &A, const MPState &B);
        MPState randState();
        TreeNode& nearest(const RRT_Tree &tree, const MPState &target);
        MPState& chooseTarget();
        MPState& extend(MPState nearest, MPState target);
        bool checkCollision(vector<Obstacle> ob_set, const MPState &st, PlannerAgentShape &agent);
        bool checkCollision(const Obstacle &obs, const MPState &st, PlannerAgentShape &agent);
        void testCollisionFunc();

    };
}


#endif // RRTPLANNER_H
