#include "rrtplanner.h"

#include <Box2D/Collision/b2Collision.h>
#include <Box2D/Common/b2Math.h>
#include <cstdlib>
#include <time.h>
#include <cmath>

using namespace Planning;

RRTPlanner::RRTPlanner()
{

}

void RRTPlanner::setInitial(const MPState &initialState)
{
    this->initial = initialState;

    srand (time(NULL));
}

void RRTPlanner::setBound(const PlannerBound b)
{
    bound = b;
}

void RRTPlanner::setAgent(const PlannerAgentShape &ag)
{
    agent = ag;
}

void RRTPlanner::setGoalState(const MPState &g)
{
    goal = g;
}

double RRTPlanner::dist(const MPState &A, const MPState &B)
{
    // euclidean dist
    MPState vec(B-A);
    return vec.lenght2D();
}

RRTPlanner::TreeNode &RRTPlanner::nearest(const RRTPlanner::RRT_Tree &tree, const MPState &target)
{
    double min_dist = INFINITY;
    TreeNode near;
    for(int i=0; i<tree.size(); i++)
    {
        TreeNode temp_node = tree.at(i);
        double temp_dist = dist(temp_node .state, target);// < min_dist;

        if(temp_dist < min_dist)
        {
            min_dist = temp_dist;
            near = temp_node ;
        }
    }
    return near;
}

MPState RRTPlanner::randState()
{
    double x_range = bound.getTopRight().X() - bound.getDownLeft().X();
    double y_range = bound.getTopRight().Y() - bound.getDownLeft().Y();
    double r1 = (double)(rand() % ((int)(x_range * 1000.0))) / 1000;
    r1 += bound.getDownLeft().X();
    double r2 = (double)(rand() % ((int)(y_range * 1000.0))) / 1000;
    r2 += bound.getDownLeft().Y();
    double r3 = (double)(rand() % ((int)(M_PI * 1000.0))) / 1000;
//    b2Vec2 point;
//    point.Set(r1, r2);
//    b2Transform transform;
//    transform.SetIdentity();
//    bool result = bound.TestPoint(transform, point);

    MPState s(r1,r2,r3);
//    if(!result)
//        s.setZero();
    return s;
}

Obstacle RRTPlanner::generateRandObstacle()
{
    Obstacle *ob;
    MPState s1;
    int r1 = rand() % 100;
    while(1) // search while a good obstacle is not found
    {
        if(r1 <= 40)
        {   // generate a rectangular obstacle
            s1 = randState();
            s1.setTeta(0);
//            s2 = randState();
            double rect_h = agent.shape->m_radius * (.2 + (double)(rand()%100)/31.0);
            double rect_w = agent.shape->m_radius * (.2 + (double)(rand()%100)/31.0);
            double rect_orien = (double)(rand()%(int)(M_PI * 1000))/1000.0;
            ob = new Obstacle(s1.to2D(), rect_w, rect_h, rect_orien, false);
            if(checkCollision(*ob, initial, this->agent) || checkCollision(*ob, goal, this->agent))
            { // the obstacle is in initial/goal zone
                delete ob;
                continue;
            }
            break;
        }

        else // generate a circular obstacle
        {
            s1 = randState();
            double rad = agent.shape->m_radius * (.2 + (double)(rand()%100)/51.0);

            ob = new Obstacle(s1.to2D(), rad, false);  // circle with radius = 2.0
            if(checkCollision(*ob, initial, this->agent) || checkCollision(*ob, goal, this->agent))
            { // the obstacle is in initial/goal zone
                delete ob;
                continue;
            }
            break;
        }
    }

    return *ob;
}

MPState &RRTPlanner::extend(MPState nearest, MPState target)
{
    MPState diff(target - nearest);
    diff.normalize2D();
    diff *= 2*agent.shape->m_radius;
    MPState *newState = new MPState(nearest + diff);
    bool col = checkCollision(this->obstacleList, *newState, agent);    
    if(!col)
        return *newState;
//    delete newState;
//    w.addRobotState(*newState, 0);
    MPState s;
    return s;
}

MPPlan RRTPlanner::getPlan()
{
    vector<MPState> path;
    MPState A = goal;
    TreeNode last = nearest(rrtTree, A);

    while(last.fatherIndex != -1)
    {
        path.push_back(last.state);
        last = rrtTree.at(last.fatherIndex);
    }
    return path;
}

void RRTPlanner::plan()
{
    double start_time = getCurrentTimeMiliSec();
    rrtTree.clear();
    int tryExtensionCounter = 0;
    int insertCounter = 0;
    rrtTree.push_back(TreeNode(initial, tryExtensionCounter, -1, 0));
    while(1)
    {
        tryExtensionCounter ++;
        MPState target = chooseTarget();
        TreeNode near = nearest(rrtTree, target);
        MPState extended = extend(near.state, target);
        if(!extended.isNull())
        {
            insertCounter ++;
            rrtTree.push_back(TreeNode(extended, insertCounter, near.index, near.depth+1));
        }
        else
        {
//            cout << "and state " << counter << endl;
        }

        near = nearest(rrtTree, goal);
        double d = dist(goal, near.state);
        double reachTargetDist = agent.shape->m_radius;
        if(d < reachTargetDist)
        {
            plannerSucceed = true;
            break;
        }
        if(rrtTree.size() >= MAX_TREE_NODE)
        {
            cerr << "Tree Capacity exceeds " << MAX_TREE_NODE << endl;
            plannerSucceed = false;
            break;
        }
        if(tryExtensionCounter >= MAX_EXTENSION_TRY)
        {
            cerr << "Node Extension Counter exceeds " << MAX_EXTENSION_TRY << endl;
            plannerSucceed = false;
            break;
        }
    }

    if(plannerSucceed)
    {
        cout << "Succesful Planning" << endl ;
    }

    double end_time = getCurrentTimeMiliSec();
    this->planningTime = end_time - start_time;
    cout << "Time for Naive RRT Planning" << planningTime << "mili seconds" << endl;

}

void RRTPlanner::greedyPlan()
{
    double start_time = getCurrentTimeMiliSec();

    double reachTargetDist = agent.shape->m_radius;
    rrtTree.clear();
    int tryExtensionCounter = 0;
    rrtTree.push_back(TreeNode(initial, tryExtensionCounter, -1, 0));
    int insertCounter = 0;

    while(1)
    {
        MPState target = chooseTarget();
        int greedyCounter = 0;
        while(1){
            tryExtensionCounter ++;
            TreeNode near = nearest(rrtTree, target);
            MPState extended = extend(near.state, target);
            bool extensionSucceed = !extended.isNull();
            if(!extensionSucceed)
                break;
            insertCounter ++;
            rrtTree.push_back(TreeNode(extended, insertCounter, near.index, near.depth +1));
            if(dist(target, extended) < reachTargetDist)
                break;
            if(target != goal)
                break;
            greedyCounter ++;
            if(greedyCounter>5)
                break;
        }

        TreeNode near = nearest(rrtTree, goal);
        double d = dist(goal, near.state);
        if(d < reachTargetDist)
        {
            plannerSucceed = true;
            break;
        }
        if(rrtTree.size() >= MAX_TREE_NODE)
        {
            cerr << "Tree Capacity exceeds " << MAX_TREE_NODE << endl;
            plannerSucceed = false;
            break;
        }
        if(tryExtensionCounter >= MAX_EXTENSION_TRY)
        {
            cerr << "Node Extension Counter exceeds " << MAX_EXTENSION_TRY << endl;
            plannerSucceed = false;
            break;
        }
    }

    if(plannerSucceed)
    {
        cout << "Succesful Planning" << endl ;
    }

    double end_time = getCurrentTimeMiliSec();
    this->planningTime = end_time - start_time;
    cout << "Time for Naive RRT Planning" << planningTime << "mili seconds" << endl;

}

MPState &RRTPlanner::chooseTarget()
{
    double p1 = .35;
    double r = double(rand() % 1000) / 1000.0;
    if(r < p1)
        return goal;
    MPState rand = randState();
    return rand;
}

bool RRTPlanner::checkCollision(vector<Obstacle> ob_set, const MPState &st, PlannerAgentShape &agent)
{
    b2Transform stateTransform, obsTransform;
    stateTransform.Set(b2Vec2(st.X(), st.Y()), st.Teta());

    for(int i=0; i<ob_set.size(); i++)
    {
        Obstacle obs = ob_set[i];
        obsTransform.Set(b2Vec2(obs.Center.X(), obs.Center.Y()), obs.orien);
        bool result = b2TestOverlap(obs.shape, 0, agent.shape, 1, obsTransform, stateTransform);
        if(result)
        {
//            cout << "collision between obstacle " << i;
            return true;
        }

    }

    return false;
}

bool RRTPlanner::checkCollision(const Obstacle &obs, const MPState &st, PlannerAgentShape &agent)
{
    b2Transform stateTransform, obsTransform;
    stateTransform.Set(b2Vec2(st.X(), st.Y()), st.Teta());

    obsTransform.Set(b2Vec2(obs.Center.X(), obs.Center.Y()), obs.orien);

    return b2TestOverlap(obs.shape, 0, agent.shape, 1, obsTransform, stateTransform);
}

double RRTPlanner::getCurrentTimeMiliSec()
{
    ptime t1(microsec_clock::universal_time());
    time_duration td = t1.time_of_day();
    double time_ =  td.total_microseconds()/1000.0;
    return time_;
}

void RRTPlanner::testCollisionFunc()
{
    for(int i=0; i<this->rrtTree.size(); i++)
        checkCollision(this->obstacleList, this->rrtTree.at(i).state, this->agent);
}

PlannerAgentShape::PlannerAgentShape(b2Shape::Type type)
{
    switch(type)
    {
    case b2Shape::e_circle:
        shape = new b2CircleShape();
        break;

    case b2Shape::e_polygon :
        shape = new b2PolygonShape();
        break;
    }

}

PlannerAgentShape &PlannerAgentShape::operator =(const PlannerAgentShape &other)
{
    this->shape->m_radius = other.shape->m_radius;
    this->max_vel =  other.max_vel;
    this->max_rot = other.max_rot;
    this->mass = other.mass;
    this->init_position = other.init_position;
}


PlannerBound::PlannerBound()
{
    this->topBound = INFINITY;
    this->downBound = -INFINITY;
    this->rightBound = INFINITY;
    this->leftBound = -INFINITY;
}

PlannerBound::PlannerBound(double left, double down, double right, double top)
{
    this->set(top, down, right, left);
}

void PlannerBound::set(double left, double down, double right, double top)
{
    this->topBound = top;
    this->downBound = down;
    this->rightBound = right;
    this->leftBound = left;
}

void PlannerBound::set(Vector2D downLeft, Vector2D topRight)
{
    this->leftBound = downLeft.X();
    this->downBound = downLeft.Y();
    this->rightBound = topRight.X();
    this->topBound = topRight.Y();
}

bool PlannerBound::isEmpty()
{
    if(this->topBound == this->downBound || this->rightBound == this->leftBound)
        return true;
    return false;
}

Vector2D PlannerBound::getTopLeft()
{
    Vector2D v(leftBound, topBound);
    return v;
}

Vector2D PlannerBound::getTopRight()
{
    Vector2D v(rightBound, topBound);
    return v;
}

Vector2D PlannerBound::getDownLeft()
{
    Vector2D v(leftBound, downBound);
    return v;
}

Vector2D PlannerBound::getDownRight()
{
    Vector2D v(rightBound, downBound);
    return v;

}
