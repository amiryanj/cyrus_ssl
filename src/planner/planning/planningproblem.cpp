#include "planningproblem.h"
#include "plannermath.h"
#include <Box2D/Collision/b2Distance.h>

using namespace MyMath;

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
    trajec.clear();
    double start_time = MyMath::currentTimeMSec();
    tree.addNewVertex(NULL, initialState);
    for(unsigned int i=0; i< MAX_RRT_STEP_TRY ; ++i)
    {
        if(RRTStep() == Reached)
        {
            this->planningResult = true;
            buildTrajectory();
            double finish_time = MyMath::currentTimeMSec();
            this->planningTime = finish_time - start_time;
            break;
        }
    }
}

void PlanningProblem::ERRTsolve()
{

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
        if(EucleadianDistance(new_st, goal.goal_point) < agent.shape->m_radius)
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
    this->trajec.clear();
    if(planningResult)
    {
        RRTVertex* last_vertex = tree.nearest(goal.goal_point);
        trajec.prependVertex(last_vertex);
        while (last_vertex->parent != NULL)
        {
            trajec.prependVertex(last_vertex->parent);
            last_vertex = last_vertex->parent;
        }

        if(!(last_vertex->state == this->initialState))
        {
            cerr << "this is a bug : trajectory is invalid" << endl ;
        }
        trajec.setRoot(last_vertex);
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
    tree.clear();
    trajec.clear();
    double repulsive_coefficient = 6;
    double start_time = MyMath::currentTimeMSec();
    tree.addNewVertex(NULL, initialState);
    RRTVertex* near = tree.nearest(goal.goal_point);

    for(int step = 0; step < 50; step++)
    {
        b2PolygonShape road_to_goal_shape;
        b2Vec2 center(((near->state.position + goal.goal_point.position)/2.0).to2D().b2vec2());
        Vector2D diff_to_goal((goal.goal_point.position - near->state.position).to2D());

//        double angle = M_PI_2 + atan2(diff_to_goal.Y(), diff_to_goal.X());
        road_to_goal_shape.SetAsBox(agent.shape->m_radius * 1.10, diff_to_goal.lenght()/2, center,
                      M_PI_2 + atan2(diff_to_goal.Y(), diff_to_goal.X()));
/*
        // debug
//        cout<< "Angle : " << angle << endl ;
//        cout << "road box: " << endl;
//        for (int ii=0; ii<4; ii++)
//            cout << "x: " << road.GetVertex(ii).x << " y: " << road.GetVertex(ii).y << endl;
*/

        diff_to_goal.normalize();
        b2Transform identity_trans;
        identity_trans.SetIdentity();
        for(unsigned int i=0; i<this->stat_obstacles.size(); i++)
        {
            Obstacle* ob = stat_obstacles.at(i);
            if(b2TestOverlap(ob->shape, 0, &road_to_goal_shape, 1, ob->transform, identity_trans))
            {
                Vector2D diff_to_ob(near->state.position.to2D() - Vector2D(ob->transform.p));
                /*
//                if(ob->shape->m_type == b2Shape::e_circle)
//                {
//                    Vector2D vec_diff(diff_to_ob); // diff from state to center of obstacle
//                    vec_diff.normalize();
//                    vec_diff *= ob->shape->m_radius * -1; // a vector from obstacle center to its body
//                    vec_diff = vec_diff + Vector2D(diff_to_ob);
//                }
//                else {
//                }  */

//                if(ob->shape->m_type == b2Shape::e_circle)
//                    radius = ob->shape->m_radius;
//                else

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
                double min_dist_to_ob = dis_out.distance;

                // debug

                cout << "min dist from [" << near->state.position.X() << ","
                     << near->state.position.Y() << "] is :" << min_dist_to_ob << endl;

                Vector2D repulse_vec(diff_to_ob);
                repulse_vec.normalize();
                repulse_vec *= (agent.shape->m_radius * repulsive_coefficient/diff_to_ob.lenght());

                diff_to_goal += repulse_vec;
            }
        }
        diff_to_goal.normalize();

        Station new_station;
        new_station.setPosition(near->state.position + (diff_to_goal * 1.7 * agent.shape->m_radius).to3D());
        if(CheckValidity(new_station))
        {
            tree.addNewVertex(near, new_station);
            near = tree.lastAddedVertex();
            repulsive_coefficient *= 0.98;
            cout << "repulsive_coefficient = " << repulsive_coefficient << endl;
            if(EucleadianDistance(near->state, goal.goal_point) < agent.shape->m_radius)
            {
                this->planningResult = true;
                double finish_time = currentTimeMSec();
                double total_time = finish_time - start_time;
                cout << "Planning Succeed in (ms): " << total_time << endl;
                return;
            }
        }
        else
        {
            cerr << "Potential Field: problem in finding root (local minima)" << endl;
            repulsive_coefficient *= 1.3;
            cout << "repulsive_coefficient = " << repulsive_coefficient << endl;
        }

    }

}
