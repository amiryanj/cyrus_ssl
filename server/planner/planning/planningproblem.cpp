#include "planningproblem.h"
#include <Box2D/Collision/b2Distance.h>
#include <iostream>
#include "plannermath.h"
#include "math/sslmath.h"

using namespace SSL;

PlanningProblem::PlanningProblem() {
    identity_trans.SetIdentity();
}

bool PlanningProblem::solve()
{
    double start_time = currentTimeMSec();
    planningResult = false;

    if (!CheckValidity(goal.goal_point)) {
        cerr << "Warning: the Goal state is drawn in an obstacle" << endl;
        solveInvalidGoalState();
    }

    if(goal.minDistTo(initialState) == 0) { // if it is already in the goal region
        tree.clear();
        trajec.clear();
        planningResult = true;
    }

    else if(!CheckValidity(initialState))
        solveInvalidInitialState();

    else {
        PotentialFieldSolve();
        if(!planningResult)
            GRRTsolve();
        if(!planningResult)
            RRTsolve();
        buildTrajectory();
    }

    buildVelocityProfile();
//    trajec.printToStream(cout);

    double finish_time = currentTimeMSec();
    double total_time = finish_time - start_time ;
    cout << "Planning Succeed in (ms): " << total_time << endl;
    return planningResult;
}

void PlanningProblem::PotentialFieldSolve()
{
//    this->planningResult = false;
    tree.clear();  // all planning solvers should clear tree before planning
    trajec.clear();
    int extendFailureCounter = 0;
    double start_time = currentTimeMSec();
    RRTVertex* currentVertex = tree.addNewVertex(NULL, initialState);

    for(int step = 0; step < MAX_RRT_STEP_TRY; step++)
    {
        Vector2D totalForce(0, 0);
        b2PolygonShape road_to_goal_shape;
        b2Vec2 center(((currentVertex->state.position + goal.goal_point.position)/2.0).toB2vec2());
        Vector2D diff_to_goal((goal.goal_point.position - currentVertex->state.position).to2D());

        road_to_goal_shape.SetAsBox(agent.shape->m_radius * 1.10, diff_to_goal.lenght()/2, center,
                      M_PI_2 + atan2(diff_to_goal.Y(), diff_to_goal.X()));

        diff_to_goal.normalize();

        for(unsigned int i=0; i<this->stat_obstacles.size(); i++)
        {
            Obstacle* ob = stat_obstacles.at(i);
            if(ob == NULL)
                continue;
            if(b2TestOverlap(ob->shape, 0, &road_to_goal_shape, 1, ob->m_transform, identity_trans))
            { // if straight path collides with this obstacle
                Vector2D diff_to_ob(currentVertex->state.position.to2D() - Vector2D(ob->m_transform.p));

//                b2DistanceProxy state_proxy;
//                state_proxy.Set(agent.shape, 0);
//                b2DistanceProxy ob_proxy;
//                ob_proxy.Set(ob->shape, 1);
//                b2DistanceInput dis_in;
//                dis_in.proxyA = state_proxy;
//                dis_in.proxyB = ob_proxy;
//                dis_in.transformA = b2Transform(currentVertex->state.position.to2D().b2vec2(),
//                                                                  b2Rot(currentVertex->state.getPosition().Teta()));
//                dis_in.transformB = ob->m_transform;
//                b2SimplexCache dis_cache_;
//                dis_cache_.count = 0;
//                b2DistanceOutput dis_out;
//                b2Distance(&dis_out, &dis_cache_, &dis_in);
                // the obstacles are circular
//                assert(ob->shape->m_type == b2Shape::e_circle);
                float dist_to_ob_body = diff_to_ob.lenght() - (ob->shape->m_radius + agent.shape->m_radius);

                float repulseMag;
                // avoiding divid by zero
                float minRadius = agent.shape->m_radius *(0.8) + ob->shape->m_radius *(0.2);
//                if(ob->shape->m_radius > agent.shape->m_radius)

                if(dist_to_ob_body < minRadius * 1.5) // 1.5*9cm = 13.5cm
                    repulseMag = 1;
                else if(dist_to_ob_body < minRadius * 6) // 6*9cm = 54cm
                    repulseMag = 1 - (dist_to_ob_body/(minRadius * 6));
                else
                    continue; // dont consider this obstacle at all

                Vector2D obstacleForce;
                obstacleForce += diff_to_ob.normalized() * repulseMag;
                obstacleForce += diff_to_goal;
                obstacleForce.normalize();

                totalForce += obstacleForce;
            }
        }

        totalForce += diff_to_goal;
        totalForce.normalize();

        Station new_station;
        new_station.setPosition(currentVertex->state.position + (totalForce * 1.3 * agent.shape->m_radius).to3D());
        for(uint i=0; i<stat_obstacles.size(); i++) {
            Obstacle* ob_i = stat_obstacles[i];
            assert(ob_i != NULL);
            if(hasCollision(new_station, *ob_i)) {
                Vector2D dir_ = new_station.position.to2D() - Vector2D(ob_i->m_transform.p);
                dir_.normalize();
                new_station.position = new_station.position + (dir_ * agent.shape->m_radius * 1.2).to3D();

            }
        }
        if(CheckValidity(new_station)) {
            currentVertex = tree.addNewVertex(currentVertex, new_station);

            if(EucleadianDistance(currentVertex->state, goal.goal_point) < agent.shape->m_radius * 1.6) {
                planningResult = true;
                double finish_time = currentTimeMSec();
                double total_time = finish_time - start_time;
                cout << "Potential Field Time: " << total_time << " milli second"<< endl;
                break;
            }
        }

        else {
            cerr << "extension failed in planning:";
            new_station.printToStream(cerr);
            extendFailureCounter++;
            if(extendFailureCounter > 10 && currentVertex->hasParent())
                currentVertex = currentVertex->parent;
            if(extendFailureCounter > 20)
                break;
            cerr << "Potential Field: problem in finding root (local minima)" << endl;
        }
    }
}

void PlanningProblem::GRRTsolve()
{
    this->planningResult = false;
    tree.clear();
    float start_time = SSL::currentTimeMSec();
    int tryExtensionCounter = 0;
    tree.addNewVertex(NULL, initialState);

    for(int step=0; step < MAX_RRT_STEP_TRY; step++)
    {
        GoalState target;
        float toss = uni_rand(0, 1);
        if(toss < GOAL_PROB)
            target.goal_point.set(goal.goal_point);
        else {
            Station temp = SampleStateUniform();
            target.goal_point.set(temp);
        }

        if(!target.goal_point.isValid())
            throw "can not sampled!";
        RRTVertex* near_ver = tree.nearest(target.goal_point);

        int greedyCounter = 0;
        while(greedyCounter < 5){
            tryExtensionCounter ++;
            Station extended = RRTExtend(near_ver->state, target.goal_point);
            if(!extended.isValid())
                break;
            tree.addNewVertex(near_ver, extended);
            if(target.minDistTo(extended) < agent.shape->m_radius * 1.8) {
                if(target.goal_point == goal.goal_point)
                    planningResult = true;
                break;
            }
//            if(target != goal.goal_point)  break;
            greedyCounter ++;
        }

    }

    if(planningResult)
    {
        buildTrajectory();
        float finish_time = SSL::currentTimeMSec();
        this->planningTime = finish_time - start_time;
        cout << "Greedy RRT Planning succeed in " << planningTime << "mili seconds" << endl;
    }
}

void PlanningProblem::deactive()
{
    this->trajec.clear();
    this->tree.clear();
}

void PlanningProblem::ERRTsolve()
{
    cout << "ERRT method is not implemented yet!!!" << endl;
}

void PlanningProblem::RRTsolve()
{
    this->planningResult = false;
    tree.clear();
//    trajec.clear();
    float start_time = SSL::currentTimeMSec();
    tree.addNewVertex(NULL, initialState);
    for(unsigned int i=0; i< MAX_RRT_STEP_TRY ; ++i)
    {
        if(RRTStep() == Reached)
        {
            this->planningResult = true;
            buildTrajectory();
            float finish_time = SSL::currentTimeMSec();
            this->planningTime = finish_time - start_time;
            break;
        }
    }
}

Station PlanningProblem::RRTExtend(const Station &start, const Station &target)
{
    Vector3D diff_vec = target.getPosition() - start.getPosition();
    diff_vec.normalize2D();
    diff_vec *= 2*agent.shape->m_radius;
    Station temp_station;
    temp_station.setPosition(diff_vec + start.getPosition());
    bool valid = CheckValidity(temp_station);
    if(valid)
        return temp_station;
    return Station();
}

PlanningProblem::ExtendResult PlanningProblem::RRTStep()
{
    ExtendResult result;
    try {
        Station rand_st;
        float toss = uni_rand(0, 1);
        if(toss < GOAL_PROB)
            rand_st.set(goal.goal_point);
        else
        {
            Station temp = SampleStateUniform();
            rand_st.set(temp);
        }

        if(!rand_st.isValid())
            throw "can not sampled!";
        RRTVertex* near_ver = tree.nearest(rand_st);

        //    if(near_ver->state.isValid())
        if(near_ver == NULL)
            throw "can not find nearest!";

        Station new_st = RRTExtend((near_ver->state), rand_st);
        if(!new_st.isValid())
        {
            result = Trapped;
            throw "can not extend tree!";
        }
        if(goal.minDistTo(new_st) < agent.shape->m_radius)
            result = Reached;
        else
            result = Advanced;
        tree.addNewVertex(near_ver, new_st);

    } catch (const char* msg)
    {
        cerr << "Exception in RRTStep: " << msg << endl;
    }
    return result;
}

void PlanningProblem::buildTrajectory()
{
    this->trajec.clear();  // it doesnt delete the pointers, just clears the vector

    // build path (backward direction)
    if(planningResult) {
        RRTVertex* last_vertex = tree.nearest(goal.goal_point);
        trajec.prependVertex(last_vertex);
        last_vertex->child = NULL;

        RRTVertex* parent = last_vertex->parent;
        while (parent != NULL) {
            trajec.prependVertex(parent);
            parent->child = last_vertex;
            last_vertex = parent;
            parent = last_vertex->parent;
        }
        assert(last_vertex->state == this->initialState);
    }
}

void PlanningProblem::buildVelocityProfile()
{
    // build velocity directions (forward direction)
    if(trajec.lenght() == 0) return;
    for(uint i=0; i<trajec.lenght(); i++) {
        RRTVertex* node = trajec.getVertex(i);
        RRTVertex* child = node->child;
        if(child == NULL) continue;
        Vector3D diff = child->state.position - node->state.position;
        diff.normalize2D();
        node->state.velo = diff;
        continue; // fake statement
    }

    // build teta profile (forward direction)
    trajec.getVertex(0)->state.position.setTeta(initialState.position.Teta());
    float align_radius = 600; // millimeter
    bool myFlag = false;
    float start_teta, MADTG;
    for(uint i=0; i<trajec.lenght(); i++) {
        RRTVertex* current_node = trajec.getVertex(i);
        RRTVertex* parent = current_node->parent;
        if(parent == NULL) continue;
        float dist_to_parent = (current_node->state.position - parent->state.position).lenght2D();
        float min_reach_time = 2.2 * dist_to_parent / agent.velocity_limit.to2D().lenght();
        float rotate_val;
        float MDTG = goal.minDistTo(current_node->state); // min dist to goal
        if(MDTG > align_radius) {
            float d_teta_a = SSL::minimumRequiredRotationToReachAngleRange(parent->state.position.Teta(),
                                        current_node->state.velo.to2D().arctan(), current_node->state.velo.to2D().arctan());
            float d_teta_b = SSL::minimumRequiredRotationToReachAngleRange(parent->state.position.Teta(),
                                        M_PI+current_node->state.velo.to2D().arctan(), M_PI+current_node->state.velo.to2D().arctan());
            float d_teta = (fabs(d_teta_a) < fabs(d_teta_b))? d_teta_a:d_teta_b;
            assert(fabs(d_teta) < M_PI);
            rotate_val = agent.velocity_limit.Teta() * min_reach_time * sin(d_teta/2);
            current_node->state.position.setTeta(parent->state.position.Teta() + rotate_val);
        }
        else { // in the align teta circle
            if(!myFlag) {
                start_teta = current_node->state.position.Teta();
                myFlag = true;
                float target_teta_s = goal.goal_point.position.Teta() - goal.tolerance.position.Teta();
                float target_teta_e = goal.goal_point.position.Teta() + goal.tolerance.position.Teta();
                MADTG = SSL::minimumRequiredRotationToReachAngleRange(start_teta, target_teta_s, target_teta_e);
                if(MADTG == 0)
                    break;
            }
            float linear_dist = (align_radius/2 - MDTG) / align_radius;
            float non_linear_dist = (atan(5 * linear_dist) + M_PI_2)/M_PI;
            float desired_teta = non_linear_dist * MADTG + start_teta;
            current_node->state.position.setTeta(desired_teta);
            rotate_val = desired_teta - parent->state.position.Teta();
        }
//        parent->state.velo.setTeta(rotate_val/min_reach_time);
        parent->state.velo.setTeta(rotate_val/M_PI);  // set robot omega (Angular velocity)

    }

    align_radius = 700; // for adjusting robot desired speed
    for(int i=0; i<trajec.lenght(); i++) {
        RRTVertex* node = trajec.getVertex(i);
        float MDTG = goal.minDistTo(node->state); // min dist to goal
        if(MDTG > align_radius) {
//            node->state.velo = node->state.velo.dotProduct(agent.velocity_limit);
        }
        else { // in the align velocity circle
            float omega = node->state.velo.Teta();
            node->state.velo = node->state.velo * (MDTG)/align_radius;
            node->state.velo.setTeta(omega);
        }
    }
}

void PlanningProblem::solveInvalidInitialState()
{
    // if the robot is in an invalid position, find the shotest path to valid area
    if(!CheckValidity(initialState)) {
        cerr << "Warning: the initial state is drawn in an obstacle" << endl;
        tree.clear();
        trajec.clear();
        RRTVertex* near = tree.addNewVertex(NULL, initialState);
        for(unsigned int i=0; i < stat_obstacles.size(); i++)  {
            Obstacle* ob = stat_obstacles.at(i);
            if(ob==NULL)
                continue;
            if(hasCollision(initialState, *ob)) {
                Vector2D diff_to_ob(initialState.position.to2D() - Vector2D(ob->m_transform.p));
                diff_to_ob.normalize();
                Station new_station;
                new_station.setPosition(initialState.position + (diff_to_ob * ob->shape->m_radius).to3D());
                tree.addNewVertex(near, new_station);
                RRTVertex* newVer = tree.lastAddedVertex();
                newVer->child = near;
                this->trajec.prependVertex(newVer);
                this->trajec.prependVertex(near);
                near->child = newVer;
                planningResult = true;
                trajec.printToStream(cout);
                return;
            }
        }
    }
}

void PlanningProblem::solveInvalidGoalState()
{
    for(uint i=0; i<stat_obstacles.size(); i++) {
        Obstacle* ob = stat_obstacles[i];
        if(ob == NULL) continue;
        if(hasCollision(goal.goal_point, *ob)) {
            Vector2D diff = goal.goal_point.position.to2D() - Vector2D(ob->m_transform.p);
            float displacement_ = agent.shape->m_radius + ob->shape->m_radius - diff.lenght();
            if(displacement_ > 0)
                goal.goal_point.position = goal.goal_point.position + (diff.normalized() * displacement_ * 1.1).to3D();
            break;
        }

        // TODO : make a strategy for handling this situation
            //
    }
}

float PlanningProblem::EucleadianDistance(const Station &A, const Station &B)
{
    return (B.getPosition() - A.getPosition()).lenght2D();
}

bool PlanningProblem::hasCollision(Station &st, const ObstacleSet &ob_set)
{
    b2Transform st_ateTransform;
    st_ateTransform.Set(st.position.toB2vec2(), st.position.Teta());

    for(unsigned int i=0; i<ob_set.size(); i++)
    {
        Obstacle* ob = ob_set[i];
        if(ob == NULL)
            continue;
        bool result = b2TestOverlap(ob->shape, 0, agent.shape, 1, ob->m_transform, st_ateTransform);
        if(result)
        {
            std::cout << "collision with obstacle " << i << endl;
            return true;
        }
    }
    return false;
}

bool PlanningProblem::hasCollision(Station &st, const Obstacle &ob)
{
    b2Transform st_Transform;
    st_Transform.Set(st.position.toB2vec2(), st.position.Teta());

    return b2TestOverlap(ob.shape, 0, agent.shape, 1, ob.m_transform, st_Transform);
}

bool PlanningProblem::CheckValidity(Station &A)
{
    if(hasCollision(A, this->stat_obstacles))
        return false;
    if(hasCollision(A, this->dyna_obstacles))
        return false;
    return true;
}

Station PlanningProblem::SampleStateUniform()
{
    float rt = uni_rand(0, M_2_PI);
    Station temp_station;
    for(int i=0; i < MAX_SAMPLING_TRY; ++i)
    {
        float rx = uni_rand(bound.getDownLeft().X(), bound.getTopRight().X());
        float ry = uni_rand(bound.getDownLeft().Y(), bound.getTopRight().Y());
        temp_station.setPosition(Vector3D(rx, ry, rt));
        if(CheckValidity(temp_station))
            return temp_station;
    }
    return Station();
}



void PlanningProblem::setPlanningAgent(PlanningAgent ag)
{
    this->agent = ag;
}

PlanningAgent PlanningProblem::getPlanningAgent() const
{
    return this->agent;
}

void PlanningProblem::setInitialState(Station st)
{
    this->initialState = st;
}

Station PlanningProblem::getInitialState() const
{
    return this->initialState;
}

void PlanningProblem::setGoalRegion(GoalState gl)
{
    this->goal = gl;
}

GoalState PlanningProblem::getGoal()
{
    return this->goal;
}

void PlanningProblem::setGoalPoint(Station st)
{
    this->goal.goal_point.set(st);
}

void PlanningProblem::setBound(FieldBound bn)
{
    this->bound = bn;
}

FieldBound PlanningProblem::getBound() const
{
    return this->bound;
}

void PlanningProblem::setStaticObstacles(ObstacleSet st_obs)
{
    this->stat_obstacles = st_obs;
}

ObstacleSet PlanningProblem::getStaticObstacles() const
{
    return this->stat_obstacles;
}

void PlanningProblem::setDynamicObstacles(ObstacleSet dy_obs)
{
    this->dyna_obstacles = dy_obs;
}

void PlanningProblem::clearObstacles()
{
    for(int i=stat_obstacles.size()-1; i>=0; i--)
    {
        Obstacle* ob = (Obstacle*)stat_obstacles.at(i);
        if(ob != NULL)
            delete ob;
    }

    this->stat_obstacles.clear();

    for(int i=dyna_obstacles.size()-1; i>=0; i--)
    {
        Obstacle* ob = (Obstacle*)dyna_obstacles.at(i);
        if(ob != NULL)
            delete ob;
    }
    this->dyna_obstacles.clear();
}

RandomTree PlanningProblem::getTree() const
{
    return tree;
}

Trajectory PlanningProblem::getTrajectory() const
{
    return trajec;
}

Velocity PlanningProblem::getControl(unsigned int i)
{
    Velocity c;
    if(i < trajec.lenght()) {
        Station st = trajec.getStation(i);
        c = st.velo;
    }
    else
        c.setZero();
    return c;
}
