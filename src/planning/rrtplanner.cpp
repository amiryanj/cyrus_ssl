#include "rrtplanner.h"

#include <Box2D/Collision/b2Collision.h>
#include <Box2D/Common/b2Math.h>
#include <cstdlib>
#include <time.h>
#include <cmath>

using namespace Planner;

RRTPlanner::RRTPlanner()
{
//    new PlannerAgent(b2Shape::e_circle);
}

void RRTPlanner::initialize(const State &initialState, PlannerBound b )
{
//    if(!b.isEmpty())
//        this->setBound(b);
    this->initial = initialState;

    srand (time(NULL));
}

void RRTPlanner::setBound(PlannerBound b)
{
    bound = b;
}

void RRTPlanner::setAgent(const PlannerAgent &ag)
{
    agent = ag;
}

void RRTPlanner::setGoalState(const State &g)
{
    goal = g;
}

//double RRTPlanner::dist(const State &A, const State &B)
//{
//    // euclidean dist
//    State vec(B-A);
//    return vec.position.lenght();
//}

RRTPlanner::TreeNode &RRTPlanner::nearest(const RRTPlanner::RRT_Tree &tree, State &target)
{
    double min_dist = INFINITY;
    TreeNode near;
    for(int i=0; i<tree.size(); i++)
    {
        TreeNode temp_node = tree.at(i);
        double temp_dist = temp_node.state.distToB(target);// < min_dist;

        if(temp_dist < min_dist)
        {
            min_dist = temp_dist;
            near = temp_node ;
        }
    }
    return near;
}

State RRTPlanner::randState()
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

    State s(Vector2D(r1,r2), r3, 0);
//    if(!result)
//        s.setZero();
    return s;
}

Obstacle RRTPlanner::generateRandObstacle()
{
    Obstacle *ob;
    State s1;
    int r1 = rand() % 100;
    while(1) // search while a good obstacle is not found
    {
        if(r1 < 0)
        {   // generate a rectangular obstacle
            s1 = randState();
            s1.heading = 0;
//            s2 = randState();
            double rect_h = agent.shape->m_radius * (.2 + (double)(rand()%100)/31.0);
            double rect_w = agent.shape->m_radius * (.2 + (double)(rand()%100)/31.0);
            double rect_orien = (double)(rand()%(int)(M_PI * 1000))/1000.0;
            ob = new Obstacle(s1.position, rect_w, rect_h, rect_orien, false);
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

            ob = new Obstacle(s1.position, rad, false);  // circle with radius = 2.0
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

State *RRTPlanner::extend(State nearest, State target)
{
    State diff(target - nearest);
//    diff.position.normalize();
//    diff.position.
    double delta_x = diff.position.X() ;
    double p3 = ( target.position.Y() - ( nearest.position.Y()
                                       + delta_x * tan(nearest.heading * M_PI/180.0)
                                       + pow(delta_x, 2) * nearest.curvature / 2.0 ) ) / pow(delta_x, 3);
    delta_x = (nearest.velocity * 0.30 * 3) ;
    double ext_x = nearest.position.X() + delta_x;
    double ext_y =  nearest.position.Y()
            + pow(delta_x, 1) * tan(nearest.heading * M_PI/180.0)
            + pow(delta_x, 2) * nearest.curvature / 2.0
            + pow(delta_x, 3) * p3;
    double ext_heading =  (tan(nearest.heading * M_PI/180.0)
            + pow(delta_x, 1) * 2 * nearest.curvature / 2.0
            + pow(delta_x, 2) * 3 * p3) * 180.0 / M_PI;
    double ext_curv = 2 * nearest.curvature / 2.0
            + pow(delta_x, 1) * 6 * p3;
    double ext_velo = nearest.velocity;

    State *newState = new State(Vector2D(ext_x, ext_y), ext_heading, ext_velo);
    newState->curvature = ext_curv;

    if(newState->position.X() > bound.rightBound || newState->position.X() < bound.leftBound)
        return NULL;
    if(newState->position.Y() > bound.topBound || newState->position.Y() < bound.downBound)
        return NULL;

    bool col = checkCollision(this->obstacleList, *newState, agent);    
    if(!col)
        return newState;
//    delete newState;
//    w.addRobotState(*newState, 0);
//    State s;  // it will be considered as null state
    return NULL;
}

vector<State> RRTPlanner::getPlan()
{
    vector<State> path;
    State A = goal;
    TreeNode last = nearest(rrtTree, A);

    while(last.fatherIndex <= -1)
    {
        path.push_back(last.state);
        last = rrtTree.at(last.fatherIndex);
    }
    return path;
}

void RRTPlanner::plan()
{
    double start_time = getTimeMiliSec();
    rrtTree.clear();
    int tryExtensionCounter = 0;
    int insertCounter = 0;
    rrtTree.push_back(TreeNode(initial, tryExtensionCounter, -1, 0));
    while(1)
    {
        tryExtensionCounter ++;
        State target = chooseTarget();
        TreeNode near = nearest(rrtTree, target);
        State *extended = extend(near.state, target);
        if(extended != NULL  )
        {
            insertCounter ++;
            rrtTree.push_back(TreeNode(*extended, insertCounter, near.index, near.depth+1));
        }
        else
        {
//            cout << "and state " << counter << endl;
        }

        near = nearest(rrtTree, goal);
        double d = near.state.distToB(goal);
        double reachTargetDist = 3 * agent.shape->m_radius;
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

    double end_time = getTimeMiliSec();
    this->planningTime = end_time - start_time;
    cout << "Time for Naive RRT Planning" << planningTime << "mili seconds" << endl;

}

void RRTPlanner::greedyPlan()
{
    double start_time = getTimeMiliSec();

    double reachTargetDist = agent.shape->m_radius;
    rrtTree.clear();
    int tryExtensionCounter = 0;
    rrtTree.push_back(TreeNode(initial, tryExtensionCounter, -1, 0));
    int insertCounter = 0;

    while(1)
    {
        State target = chooseTarget();
        int greedyCounter = 0;
        while(1){
            tryExtensionCounter ++;
            TreeNode near = nearest(rrtTree, target);
            State *extended = extend(near.state, target);
            if(extended == NULL)
                break;
            insertCounter ++;
            rrtTree.push_back(TreeNode(*extended, insertCounter, near.index, near.depth +1));
            if(target.distTo(*extended) < reachTargetDist)
                break;
            if(! (target == goal))
                break;
            greedyCounter ++;
            if(greedyCounter>5)
                break;
        }

        TreeNode near = nearest(rrtTree, goal);
        double d = goal.distTo(near.state);
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

    double end_time = getTimeMiliSec();
    this->planningTime = end_time - start_time;
    cout << "Time for Naive RRT Planning" << planningTime << "mili seconds" << endl;

}

State &RRTPlanner::chooseTarget()
{
//    double p1 = .35;
//    double r = double(rand() % 1000) / 1000.0;
//    if(r < p1)
//        return goal;
//    State rand = randState();
//    return rand;
    bool badState;
    State rnd_st;
    b2Transform transform;
    double cir_radius = initial.velocity * 5;
    b2CircleShape carBannedCircle;
    carBannedCircle.m_radius = cir_radius;

    do{
    rnd_st = randState();
//    rnd_st.position = Vector2D(-2050, 300);
    badState = (rnd_st.position.X() < initial.position.X());
    if(badState)
        continue;
    b2Vec2 cir_position = b2Vec2(initial.position.X() + cir_radius*sin(initial.heading* M_PI / 180.0),
                                 initial.position.Y() - cir_radius*cos(initial.heading* M_PI / 180.0));
    transform.Set(cir_position, 0);
    badState = carBannedCircle.TestPoint(transform, b2Vec2(rnd_st.position.X(), rnd_st.position.Y()));
    if(badState)
        continue;

    cir_position = b2Vec2(initial.position.X() - cir_radius*sin(initial.heading* M_PI / 180.0),
                                 initial.position.Y() + cir_radius*cos(initial.heading* M_PI / 180.0));
    transform.Set(cir_position, 0);
    badState = carBannedCircle.TestPoint(transform, b2Vec2(rnd_st.position.X(), rnd_st.position.Y()));

    }while(badState);

    return rnd_st;
}

bool RRTPlanner::checkCollision(ObstacleSet ob_set, const State &st, PlannerAgent &agent)
{
    b2Transform stateTransform, obsTransform;
    stateTransform.Set(b2Vec2(st.position.X(), st.position.Y()), st.heading);

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

bool RRTPlanner::checkCollision(const Obstacle &obs, const State &st, PlannerAgent &agent)
{
    b2Transform stateTransform, obsTransform;
    stateTransform.Set(b2Vec2(st.position.X(), st.position.Y()), st.heading);

    obsTransform.Set(b2Vec2(obs.Center.X(), obs.Center.Y()), obs.orien);

    return b2TestOverlap(obs.shape, 0, agent.shape, 1, obsTransform, stateTransform);
}

double RRTPlanner::getTimeMiliSec()
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
