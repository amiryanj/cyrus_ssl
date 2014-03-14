#include "planningproblem.h"
#include "plannermath.h"
#include <Box2D/Collision/b2Distance.h>
#include "tools/sslmath.h"

using namespace SSL;

PlanningProblem::PlanningProblem()
{
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
    return c;
}

void PlanningProblem::RRTsolve()
{
    this->planningResult = false;
    tree.clear();
//    trajec.clear();
    double start_time = SSL::currentTimeMSec();
    tree.addNewVertex(NULL, initialState);
    for(unsigned int i=0; i< MAX_RRT_STEP_TRY ; ++i)
    {
        if(RRTStep() == Reached)
        {
            this->planningResult = true;
            buildTrajectory();
            double finish_time = SSL::currentTimeMSec();
            this->planningTime = finish_time - start_time;
            break;
        }
    }
}

void PlanningProblem::ERRTsolve()
{

}

void PlanningProblem::GRRTsolve()
{
    this->planningResult = false;
    tree.clear();
    double start_time = SSL::currentTimeMSec();
    int tryExtensionCounter = 0;
    tree.addNewVertex(NULL, initialState);

    for(int step=0; step < MAX_RRT_STEP_TRY; step++)
    {
        GoalState target;
        double toss = uni_rand(0, 1);
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
            if(target.minDistTo(extended) < agent.shape->m_radius * 1.5) {
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
        double finish_time = SSL::currentTimeMSec();
        this->planningTime = finish_time - start_time;
        cout << "Greedy RRT Planning succeed in " << planningTime << "mili seconds" << endl;
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
        double toss = uni_rand(0, 1);
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
        if(!(last_vertex->state == this->initialState)) {
            cerr << "this is a bug : trajectory is invalid" << endl;
        }

    }

    // build velocity directions (forward direction)
    for(int i=0; i<trajec.lenght(); i++) {
        RRTVertex* node = trajec.getVertex(i);
        RRTVertex* child = node->child;
        if(child == NULL) continue;
        Vector3D diff = child->state.position - node->state.position;
        diff.normalize2D();
        node->state.velo = diff;
        continue; // fake statement
    }

    // build teta profile (forward direction)
    if(trajec.lenght() == 0) return;
    trajec.getVertex(0)->state.position.setTeta(initialState.position.Teta());
    double align_radius = 600; // millimeter
    bool myFlag = false;
    double start_teta, MADTG;
    for(int i=0; i<trajec.lenght(); i++) {
        RRTVertex* node = trajec.getVertex(i);
        RRTVertex* parent = node->parent;
        if(parent == NULL) continue;
        double dist_to_parent = (node->state.position - parent->state.position).lenght2D();
        double min_reach_time = dist_to_parent / agent.velocity_limit.to2D().lenght();
        double rotate_val;
        double MDTG = goal.minDistTo(node->state); // min dist to goal
        if(MDTG > align_radius) {
            double d_teta_a = SSL::minAngleDistToRange(node->state.position.Teta(),
                                        node->state.velo.to2D().arctan(), node->state.velo.to2D().arctan()) ;
            double d_teta_b = SSL::minAngleDistToRange(M_PI-node->state.position.Teta(),
                                        node->state.velo.to2D().arctan(), node->state.velo.to2D().arctan()) ;
            double d_teta = (fabs(d_teta_a)< fabs(d_teta_b))? d_teta_a:d_teta_b;
            rotate_val = this->agent.velocity_limit.Teta() * min_reach_time * sin(d_teta/2);
            node->state.position.setTeta(parent->state.position.Teta() + rotate_val);
            parent->state.velo.setTeta(rotate_val/min_reach_time);
        }
        else {
            if(!myFlag) {
                start_teta = node->state.position.Teta();
                myFlag = true;
                double target_teta_s = goal.goal_point.position.Teta() - goal.tolerance.position.Teta();
                double target_teta_e = goal.goal_point.position.Teta() + goal.tolerance.position.Teta();
                MADTG = SSL::minAngleDistToRange(start_teta, target_teta_s, target_teta_e);
                if(MADTG == 0)
                    break;
            }
            double linear_dist = (align_radius/2 - MDTG) / align_radius;
            double non_linear_dist = (atan(5 * linear_dist) + M_PI_2)/M_PI;
            double desired_teta = non_linear_dist * MADTG + start_teta;
            node->state.position.setTeta(desired_teta);
            rotate_val = desired_teta - parent->state.position.Teta();
            parent->state.velo.setTeta(rotate_val/min_reach_time);
        }
    }

    align_radius = 400; // for adjusting robot desired speed
    for(int i=0; i<trajec.lenght(); i++) {
        RRTVertex* node = trajec.getVertex(i);
        double MDTG = goal.minDistTo(node->state); // min dist to goal
        if(MDTG > align_radius) {
            node->state.velo = node->state.velo.dotProduct(agent.velocity_limit);
        }
        else {
            double omega = node->state.velo.Teta();
            node->state.velo = node->state.velo.dotProduct(agent.velocity_limit) * (MDTG)/align_radius;
            node->state.velo.setTeta(omega);
        }
    }
}

double PlanningProblem::EucleadianDistance(const Station &A, const Station &B)
{
    return (B.getPosition() - A.getPosition()).lenght2D();
}

bool PlanningProblem::hasCollision(Station &st, const ObstacleSet &ob_set)
{
    b2Transform st_ateTransform;
    st_ateTransform.Set(st.position.to2D().b2vec2(), st.position.Teta());

    for(unsigned int i=0; i<ob_set.size(); i++)
    {
        Obstacle* ob = ob_set[i];
        bool result = b2TestOverlap(ob->shape, 0, agent.shape, 1, ob->transform, st_ateTransform);
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
    st_Transform.Set(st.position.to2D().b2vec2(), st.position.Teta());

    return b2TestOverlap(ob.shape, 0, agent.shape, 1, ob.transform, st_Transform);
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
    double rt = uni_rand(0, M_2_PI);
    Station temp_station;
    for(int i=0; i < MAX_SAMPLING_TRY; ++i)
    {
        double rx = uni_rand(bound.getDownLeft().X(), bound.getTopRight().X());
        double ry = uni_rand(bound.getDownLeft().Y(), bound.getTopRight().Y());
        temp_station.setPosition(Vector3D(rx, ry, rt));
        if(CheckValidity(temp_station))
            return temp_station;
    }
    return Station();
}

void PlanningProblem::PotentialFieldSolve()
{
    this->planningResult = false;
    tree.clear();  // all planning solvers should clear tree before planning
    trajec.clear();
    int extendFailureCounter = 0;
    double start_time = currentTimeMSec();
    RRTVertex* near = tree.addNewVertex(NULL, initialState);

    // if the robot is in an invalid position, find the shotest path to valid area
    if(!CheckValidity(initialState)) {
        cerr << "Warning: the initial state is drawn in an obstacle" << endl;
        for(unsigned int i=0; i<this->stat_obstacles.size(); i++)  {
            Obstacle* ob = stat_obstacles.at(i);
            if(hasCollision(initialState, *ob)) {
                Vector2D diff_to_ob(initialState.position.to2D() - Vector2D(ob->transform.p));
                diff_to_ob.normalize();
                Station new_station;
                new_station.setPosition(initialState.position + (diff_to_ob * ob->shape->m_radius).to3D());
                tree.addNewVertex(near, new_station);
                RRTVertex* newVer = tree.lastAddedVertex();
                newVer->child = near;
                this->trajec.prependVertex(newVer);
                this->trajec.prependVertex(near);
                planningResult = true;
                trajec.printToStream(cout);
//                break;
                return;
            }
        }
    }

    else if(!CheckValidity(goal.goal_point))  {
        // for example: dont search
        cerr << "Warning: the Goal state is drawn in an obstacle" << endl;
    }

    else // start regular planning
    for(int step = 0; step < 300; step++)
    {
        Vector2D totalForce(0, 0);
        b2PolygonShape road_to_goal_shape;
        b2Vec2 center(((near->state.position + goal.goal_point.position)/2.0).to2D().b2vec2());
        Vector2D diff_to_goal((goal.goal_point.position - near->state.position).to2D());

        road_to_goal_shape.SetAsBox(agent.shape->m_radius * 1.10, diff_to_goal.lenght()/2, center,
                      M_PI_2 + atan2(diff_to_goal.Y(), diff_to_goal.X()));

        diff_to_goal.normalize();

        b2Transform identity_trans;
        identity_trans.SetIdentity();
        for(unsigned int i=0; i<this->stat_obstacles.size(); i++)
        {
            Obstacle* ob = stat_obstacles.at(i);
            if(b2TestOverlap(ob->shape, 0, &road_to_goal_shape, 1, ob->transform, identity_trans))
            { // if straight path collides with this obstacle
                Vector2D diff_to_ob(near->state.position.to2D() - Vector2D(ob->transform.p));

                b2DistanceProxy state_proxy;
                state_proxy.Set(agent.shape, 0);
                b2DistanceProxy ob_proxy;
                ob_proxy.Set(ob->shape, 1);
                b2DistanceInput dis_in;
                dis_in.proxyA = state_proxy;
                dis_in.proxyB = ob_proxy;
                dis_in.transformA = b2Transform(near->state.position.to2D().b2vec2(), b2Rot(near->state.getPosition().Teta()));
                dis_in.transformB = ob->transform;
                b2SimplexCache dis_cache_;
                dis_cache_.count = 0;
                b2DistanceOutput dis_out;
                b2Distance(&dis_out, &dis_cache_, &dis_in);
                double dist_to_ob_body = dis_out.distance;

                double repulseMag;
                // avoiding divid by zero
                double minRadius = agent.shape->m_radius *(0.8) + ob->shape->m_radius *(0.2);
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
        new_station.setPosition(near->state.position + (totalForce * 1.3 * agent.shape->m_radius).to3D());
        if(CheckValidity(new_station))
        {
            near = tree.addNewVertex(near, new_station);

            if(EucleadianDistance(near->state, goal.goal_point) < agent.shape->m_radius * 1.6) {
                planningResult = true;
                double total_time = currentTimeMSec() - start_time;
                cout << "Planning Succeed in (ms): " << total_time << endl;
                break;
            }
        }
        else
        {
            cerr << "extension failed in planning:";
            new_station.printToStream(cerr);
            extendFailureCounter++;
            if(extendFailureCounter > 10 && near->hasParent())
                near = near->parent;
            cerr << "Potential Field: problem in finding root (local minima)" << endl;
        }
    }
    this->buildTrajectory();
    trajec.printToStream(cout);
}
