#ifndef RRTPLANNER_H
#define RRTPLANNER_H

#include <vector>
#include <iostream>
#include "../tools/vector2d.h"
#include "../tools/vector2d.h" // x, y, teta
#include "obstacle.h"
#include <general.h>
#include <Box2D/Collision/Shapes/b2Shape.h>

#include <boost/date_time/posix_time/posix_time.hpp>
#include "state.h"
#include "plannerbound.h"
#include "planneragent.h"

using namespace boost::posix_time;

#define MAX_TREE_NODE 300
#define MAX_EXTENSION_TRY 1500

using namespace std;
using namespace Planner;

namespace Planner{

class RRTPlanner
    {
    struct TreeNode {
        TreeNode() {}
        TreeNode(State st_,int index_, int father_ind, int depth_){
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
        State state;
    };

    typedef vector<TreeNode> RRT_Tree;

    public:
        RRTPlanner();
        typedef vector<Obstacle> ObstacleSet;

        RRT_Tree rrtTree;

        State initial;
        State goal;
        PlannerBound bound;
        ObstacleSet obstacleList;

        PlannerAgent agent;
        vector<State> wayPoints;

        double planningTime;
        bool plannerSucceed;
        // ********** methods ***************************
        void initialize(const State &initialState, PlannerBound b = PlannerBound());
        void setBound(PlannerBound b);
        void setAgent(const PlannerAgent &ag);
        void setGoalState(const State &g);
        double dist(const State &A, const State &B);
        TreeNode& nearest(const RRT_Tree &tree, State &target);
        State randState();
        Obstacle generateRandObstacle();

        void plan();
        void greedyPlan();
        State& chooseTarget();
        State* extend(State nearest, State target);

        vector<State> getPlan();

        bool checkCollision(ObstacleSet ob_set, const State &st, PlannerAgent &agent);
        bool checkCollision(const Obstacle &obs, const State &st, PlannerAgent &agent);

        // time measurement
        double getTimeMiliSec();

    private:
        void testCollisionFunc();

    };
}


#endif // RRTPLANNER_H
