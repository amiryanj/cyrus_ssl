#include "planningproblem.h"
#include <Box2D/Collision/b2Distance.h>
#include "../../../common/math/sslmath.h"
#include <iostream>
//#include "../GA/planningchromosom.h"

using namespace SSL;

PlanningProblem* PlanningProblem::instance = NULL;

PlanningProblem *PlanningProblem::getInstance()
{
    if(instance == NULL)
        instance = new PlanningProblem();
    return instance;
}

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

    else {  // normal way of solvgin motion planning problem
        ObstacleSet desired_ob_set = stat_obstacles;
        desired_ob_set.insert(desired_ob_set.end(), dyna_obstacles.begin(), dyna_obstacles.end());
        vector<float> coeffs;
        for(uint i=0; i<desired_ob_set.size(); i++) {
            coeffs.push_back(1.0f);
        }
        PotentialFieldSolve(desired_ob_set, coeffs);
//        if(!planningResult) {
//            GRRTsolve();
//            buildTrajectoryFromTree();
//        }
//        if(!planningResult) {
//            RRTsolve();
//        }

        if(planningResult) {
            if(goal.minDistTo(trajec.getLastStation()) > agent.radius())
                return true;
//            computeCost(trajec);
//            // just when current plan get invalid
//            if(!checkPlanValidity(bestPlan)) {
//                checkPlanValidity(bestPlan);
//                trajec.printToStream(std::cout);
//                bestPlan.copyFrom(trajec);
//            }
//            else if(trajec.getCost() < bestPlan.getCost()) {
//                cout << "best plan:" << bestPlan.getCost() << endl;
//                cout << "last plan:" << trajec.getCost() << endl;
//                trajec.printToStream(std::cout);
//                bestPlan.copyFrom(trajec);
//            }
//            else {
//                Trajectory opt_plan = optimizePlan(bestPlan);
//                opt_plan.computeCost();
//                if(checkPlanValidity(opt_plan) && opt_plan.getCost() < bestPlan.getCost()) {
//                    bestPlan.copyFrom(opt_plan);
//                }
//
//            }
        }

    }

//    buildVelocityProfile();
//    trajec.printToStream(cout);

    double finish_time = currentTimeMSec();
    double total_time = finish_time - start_time ;
    cout << "Planning Succeed in (ms): " << total_time << endl;
    return planningResult;
}

bool PlanningProblem::testFunc()
{
    //    cout << "Test Distance Function from init state to ob_1: " << distToObstacle(initialState, *stat_obstacles[0], ) << endl;
    return false;
}

vector<Vector2D> PlanningProblem::ObstacleForces(const Station &st, const ObstacleSet &ob_set)
{
    vector<Vector2D> ob_force_list;
    ob_force_list.reserve(ob_set.size());

    float extension_len = agent.radius();
    for(uint i=0; i<ob_set.size(); i++) {
        const Obstacle* ob = ob_set[i];
        b2Vec2 agent_colid_pnt, ob_colid_pnt;
        float dist_to_ob = distToObstacle(st, *ob, agent_colid_pnt, ob_colid_pnt);
        if(dist_to_ob > extension_len * 10)   // ignore it
            continue;
        float repulse_strenght = min(extension_len /fabs(dist_to_ob), 1.099f);
        Vector2D ob_force;
        if(dist_to_ob < 0)  // in collision state
            ob_force = (st.getPosition().to2D() - Vector2D(ob->m_transform.p)).normalized() * repulse_strenght;

        else ob_force = Vector2D(agent_colid_pnt - ob_colid_pnt).normalized() * repulse_strenght;
        ob_force_list.push_back(ob_force);
    }
    return ob_force_list;
}

Vector2D PlanningProblem::RRTDirectedForce(const Station &st, Trajectory &rrt_)
{
    if(rrt_.isEmpty())
        return Vector2D(0, 0);

    float max_memberance = 0;
    int nearest_segment = -1;
    for(uint i=1; i<rrt_.length(); i++) { // it doesnt use the last segment (go towards goal on last segment)
        Vector2D pnt_1 = rrt_.getStation(i-1).getPosition().to2D();
        Vector2D pnt_2 = rrt_.getStation(i).getPosition().to2D();    

        float dist_st_segment = (st.getPosition().to2D() - pnt_1).lenght() + (st.getPosition().to2D() - pnt_2).lenght();
        float segment_len = (pnt_1 - pnt_2).lenght();

        float segment_mem = segment_len /dist_st_segment;
        if(segment_mem > max_memberance) {
            max_memberance = segment_mem;
            nearest_segment = i;
        }
    }

    if(nearest_segment == rrt_.length()-1)
        return (goal.goal_point.getPosition() - st.getPosition()).to2D().normalized();
    return (rrt_.getStation(nearest_segment).getPosition()- rrt_.getStation(nearest_segment-1).getPosition()).to2D().normalized();

}

Vector2D PlanningProblem::GoalAttractiveForce(const Station &st)
{    
    Vector2D diff_to_goal = (goal.goal_point.getPosition() - st.getPosition()).to2D();
    double stren = tanh(diff_to_goal.lenght()/25.0) + 0.1;
    return diff_to_goal.normalized() * stren;
}

Trajectory PlanningProblem::PotentialFieldSolve(const ObstacleSet &ob_set, const vector<float> &coeffs)
{
    Trajectory temp_trajec;
    temp_trajec.appendState(initialState);

    const float extension_len = agent.radius();

    for(int step = 1; step <= MAX_RRT_STEP_TRY; step++) {
        // check reaching the goal state
        Station current_station = temp_trajec.getLastStation();
        if(goal.minDistTo(current_station) < extension_len) {
            planningResult = true;
            return temp_trajec;
        }

        Vector2D total_force;
        total_force += GoalAttractiveForce(current_station);

        vector<Vector2D> ob_forces = ObstacleForces(current_station, ob_set);
        for(uint i=0; i<ob_forces.size(); i++)
            total_force += ob_forces[i] * coeffs[i];

        float delta_orien = SSL::continuousRadian(total_force.arctan() - current_station.getPosition().Teta(), -M_PI);
        float f_delta_orien = atan(delta_orien * 0.8);
        Vector2D new_pos(current_station.getPosition().to2D()
                         + Vector2D::unitVector(current_station.getPosition().Teta() + f_delta_orien/2.0) * extension_len);
        Station new_st(Vector3D(new_pos, continuousRadian(f_delta_orien +current_station.getPosition().Teta(), -M_PI)));

        temp_trajec.appendState(new_st);
    }
    return temp_trajec;
}

Trajectory PlanningProblem::RRT_APF_Solve(Trajectory &rrt_plan_, const ObstacleSet &ob_set, PlanningChromosom& params)
{
    Trajectory new_trajec;
    new_trajec.appendState(initialState);

    const float extension_len = agent.radius();

    for(int step = 1; step <= MAX_RRT_STEP_TRY; step++) {
        // check reaching the goal state
        Station current_station = new_trajec.getLastStation();
        if(goal.minDistTo(current_station) < extension_len) {
            return new_trajec;
        }

//        Vector2D diff_to_goal((goal.goal_point.getPosition() - current_station.getPosition()).to2D());
//        Vector2D attract_force = diff_to_goal.normalized();
        Vector2D total_force;

        vector<Vector2D> ob_forces = ObstacleForces(current_station, ob_set);
        for(uint i=0; i<ob_forces.size(); i++)
            total_force += ob_forces[i] * params.obstacleCoeff(i);

        total_force *= params.obstaclesTotalCoeff();

        total_force += RRTDirectedForce(current_station, rrt_plan_) * params.RRTPathCoeff();

        float delta_orien = SSL::continuousRadian(total_force.arctan() - current_station.getPosition().Teta(), -M_PI);
        float f_delta_orien = atan(delta_orien * 1.1);
        Vector2D new_pos(current_station.getPosition().to2D()
                         + Vector2D::unitVector(current_station.getPosition().Teta() + f_delta_orien/2.0) * extension_len);
        Station new_st(Vector3D(new_pos, continuousRadian(f_delta_orien +current_station.getPosition().Teta(), -M_PI)));

        new_trajec.appendState(new_st);
    }
    return new_trajec;
}

Trajectory PlanningProblem::GRRTsolve()
{
    this->planningResult = false;
    tree.clear();
    float start_time = SSL::currentTimeMSec();
    int tryExtensionCounter = 0;
    tree.addNewVertex(NULL, initialState);

    for(int step=0; step < MAX_RRT_STEP_TRY/5; step++)
    {
        Station target;
        float toss = uni_rand(0, 1);
        if(toss < GOAL_PROB)
            target.setPosition(goal.goal_point.getPosition());
        else {
            Station tempSt = SampleStateUniform();
            target.setPosition(tempSt.getPosition());
        }

        if( !target.isValid() )
            continue;
//            throw "can not sampled!";
        RRTVertex* near_ver = tree.nearest(target);
        if(near_ver == NULL)
            continue;

        int greedyCounter = 0;
        while(greedyCounter < 5){
            tryExtensionCounter ++;
            Station extended = RRTExtend(near_ver->state, target, agent.radius() * 2);
            if(!extended.isValid())
                break;
            tree.addNewVertex(near_ver, extended);
            if(Station::dubinDistance(extended, target) < agent.radius() ) {
                if((target.getPosition() - goal.goal_point.getPosition()).lenght2D() < agent.radius() /2)
                    planningResult = true;
                break;
            }
//            if(target != goal.goal_point)  break;
            greedyCounter ++;
        }

        cout << "Step = " << step << endl;

    }

    if(planningResult)
    {
        float finish_time = SSL::currentTimeMSec();
        this->planningTime = finish_time - start_time;
        cout << "Greedy RRT Planning succeed in " << planningTime << "mili seconds" << endl;
        return buildTrajectoryFromTree();
    }
    return Trajectory();
}

// *************************************************
// ************** under construction ***************
// *************************************************
Trajectory PlanningProblem::RRTConnectSolve(double arg1)
{
    double start_time = SSL::currentTimeMSec();
    tree.clear();
    backward_tree.clear();
    tree.addNewVertex(NULL, initialState);
    backward_tree.addNewVertex(NULL, goal.goal_point);

    for(uint i=0; i< MAX_RRT_STEP_TRY ; ++i)
    {
        Station randSt = SampleStateUniform();
        if(!randSt.isValid())
            continue;
        RRTVertex* near_ver = tree.nearest(randSt);
        if(near_ver == NULL)
            continue;
        Station extended_ = RRTExtend(near_ver->state, randSt, arg1);
        if(!extended_.isValid())
            continue;
        tree.addNewVertex(near_ver, extended_);

        for(int j=0; j<10; j++) {
            RRTVertex* back_near = backward_tree.nearest(extended_);
            Station back_extended = RRTExtend(back_near->state, extended_, arg1);
            if(!back_extended.isValid())
                break;
            backward_tree.addNewVertex(back_near, back_extended);

            if(Station::euclideanDistance(back_extended, extended_) < agent.radius()) {
                while(back_near != NULL) {
                    Station on_back_tree_st = back_near->state;
                    on_back_tree_st.setPosition(Vector3D(back_near->state.getPosition().to2D(),
                                                         back_near->state.getPosition().Teta() + M_PI));
                    tree.addNewVertex(tree.lastAddedVertex(), on_back_tree_st);
                    back_near = back_near->parent;
                }
                planningTime = SSL::currentTimeMSec() - start_time;
                return buildTrajectoryFromTree();
            }
        }
    }
    planningTime = SSL::currentTimeMSec() - start_time;
    return Trajectory();
}

void PlanningProblem::deactive()
{
    this->trajec.clear();
    this->tree.clear();
}

Trajectory PlanningProblem::PruneRRT(Trajectory &p, const ObstacleSet& ob_set)
{
    if(p.length() < 3)
        return p;

    Trajectory opt_plan;
    int st_index = 1;
    opt_plan.appendState(p.getStation(0));
    while((p.length() - st_index) > 1) {
        Station st_A = opt_plan.getLastStation();
        Station st_B = p.getStation(st_index +1);
        if(pathHasCollision(st_A, st_B, ob_set)) {
            opt_plan.appendState(p.getStation(st_index));
        }
        st_index ++;
    }
    opt_plan.appendState(p.getLastStation());
    return opt_plan;
//    for(int i=0; i< p.length(); i++) {
//        if(i == 0) {
//            opt_plan.appendState(p.getStation(0));
//            continue;
//        }
//        Station _st = p.getStation(i);
//        float min_dist_to_ob;
//        b2Vec2 st_colid_point;
//        b2Vec2 ob_colid_point;
//        Obstacle* ob_ = nearestObstacle(_st, stat_obstacles, min_dist_to_ob, st_colid_point, ob_colid_point);
//        if(ob_ != NULL && min_dist_to_ob < agent.radius() * 1.5) {
//            Vector2D bad_direc = (Vector2D(ob_colid_point) - Vector2D(st_colid_point)).normalized();
//            _st.setPosition(_st.getPosition() - bad_direc.to3D() * 0.5);
//        }
//        if(CheckValidity(_st))
//            opt_plan.appendState(_st);
//        else
//            opt_plan.appendState(p.getStation(i));
//    }
}

Trajectory PlanningProblem::ERRTsolve()
{
    cout << "ERRT method is not implemented yet!!!" << endl;
    assert(0);
    return Trajectory();
}

Trajectory PlanningProblem::RRTsolve(float arg1)
{
//    if(tree.count() > MAX_TREE_SIZE * 0.75)
        tree.clear();

    double start_time = SSL::currentTimeMSec();
    tree.addNewVertex(NULL, initialState);
    for(uint i=0; i< MAX_RRT_STEP_TRY ; ++i)
    {
        if(RRTStep(tree, arg1) == Reached)
        {
            this->planningResult = true;
            double finish_time = SSL::currentTimeMSec();
            this->planningTime = finish_time - start_time;
            return buildTrajectoryFromTree();
        }
    }
    double finish_time = SSL::currentTimeMSec();
    this->planningTime = finish_time - start_time;
    return Trajectory();
}

Station PlanningProblem::RRTExtend(const Station &start, const Station &target, float extension_len)
{
    Vector3D diff_vec = target.getPosition() - start.getPosition();
    diff_vec.normalize2D();
    diff_vec *= extension_len;
    float start_angle = start.getPosition().Teta();
    start_angle = SSL::continuousRadian(start_angle, diff_vec.to2D().arctan() - M_PI);
    float rotate_angle = (diff_vec.to2D().arctan() - start_angle) / 1.5;

    diff_vec.setTeta(rotate_angle);
    Station temp_station;
    temp_station.setPosition(diff_vec + start.getPosition());
    bool valid = CheckValidity(temp_station);
    if(valid)
        return temp_station;
    return Station();
}

PlanningProblem::ExtendResult PlanningProblem::RRTStep(RandomTree &r_tree, float extension_len)
{
    ExtendResult result;
    try {        
        Station rand_st;
        float toss = uni_rand(0, 1);
        if(toss < GOAL_PROB)
            rand_st.set(goal.goal_point);
        else {
            Station temp = SampleStateUniform();
            rand_st.set(temp);
        }

        if(!rand_st.isValid())
            throw "can not sampled!";
        RRTVertex* near_ver = r_tree.nearest(rand_st);

        //    if(near_ver->state.isValid())
        if(near_ver == NULL)
            throw "can not find nearest!";

        Station new_st = RRTExtend((near_ver->state), rand_st, extension_len);
        if(!new_st.isValid())
        {
            result = Trapped;
            throw "can not extend tree!";
        }
        if(goal.minDistTo(new_st) < agent.radius())
            result = Reached;
        else
            result = Advanced;
        r_tree.addNewVertex(near_ver, new_st);

    } catch (const char* msg)
    {
//        cerr << "Exception in RRTStep: " << msg << endl;
    }
    return result;
}

Trajectory PlanningProblem::buildTrajectoryFromTree()
{
    Trajectory temp_trajec;

    // build path (in backward direction)
    RRTVertex* last_vertex = tree.nearest(goal.goal_point);
    temp_trajec.appendState(last_vertex->state);
    last_vertex->child = NULL;

    RRTVertex* parent = last_vertex->parent;
    while (parent != NULL) {
        temp_trajec.prependState(parent->state);
        parent->child = last_vertex;
        last_vertex = parent;
        parent = last_vertex->parent;
    }
//        assert(last_vertex->state == this->initialState);
    return temp_trajec;


}

void PlanningProblem::buildVelocityProfile()
{
//    // build velocity directions (forward direction)
//    if(trajec.length() <= 1) return;
//    for(int i=0; i<trajec.length()-1; i++) {
//        RRTVertex* node = trajec.getStation(i);
//        RRTVertex* child = node->child;
//        if(child == NULL) continue;
//        Vector3D diff = child->state.position - node->state.position;
//        diff.normalize2D();
//        node->state.velo = diff;
//        continue; // fake statement
//    }

//    // build teta profile (forward direction)
//    trajec.getVertex(0)->state.position.setTeta(initialState.position.Teta());
//    float align_radius = 600; // millimeter
//    bool myFlag = false;
//    float start_teta, MADTG;
//    for(int i=0; i<trajec.length(); i++) {
//        RRTVertex* current_node = trajec.getVertex(i);
//        RRTVertex* parent = current_node->parent;
//        if(parent == NULL) continue;
//        float dist_to_parent = (current_node->state.position - parent->state.position).lenght2D();
//        float min_reach_time = 2.2 * dist_to_parent / agent.velocity_limit.to2D().lenght();
//        float rotate_val;
//        float MDTG = goal.minDistTo(current_node->state); // min dist to goal
//        if(MDTG > align_radius) {
//            float d_teta_a = SSL::minAngleDistToRange(parent->state.position.Teta(),
//                                        current_node->state.velo.to2D().arctan(), current_node->state.velo.to2D().arctan());
//            float d_teta_b = SSL::minAngleDistToRange(parent->state.position.Teta(),
//                                        M_PI+current_node->state.velo.to2D().arctan(), M_PI+current_node->state.velo.to2D().arctan());
//            float d_teta = (fabs(d_teta_a) < fabs(d_teta_b))? d_teta_a:d_teta_b;
//            assert(fabs(d_teta) < M_PI);
//            rotate_val = agent.velocity_limit.Teta() * min_reach_time * sin(d_teta/2);
//            current_node->state.position.setTeta(parent->state.position.Teta() + rotate_val);
//        }
//        else { // in the align teta circle
//            if(!myFlag) {
//                start_teta = current_node->state.position.Teta();
//                myFlag = true;
//                float target_teta_s = goal.goal_point.position.Teta() - goal.tolerance.position.Teta();
//                float target_teta_e = goal.goal_point.position.Teta() + goal.tolerance.position.Teta();
//                MADTG = SSL::minAngleDistToRange(start_teta, target_teta_s, target_teta_e);
//                if(MADTG == 0)
//                    break;
//            }
//            float linear_dist = (align_radius/2 - MDTG) / align_radius;
//            float non_linear_dist = (atan(5 * linear_dist) + M_PI_2)/M_PI;
//            float desired_teta = non_linear_dist * MADTG + start_teta;
//            current_node->state.position.setTeta(desired_teta);
//            rotate_val = desired_teta - parent->state.position.Teta();
//        }
////        parent->state.velo.setTeta(rotate_val/min_reach_time);
//        parent->state.velo.setTeta(rotate_val/M_PI);  // set robot omega (Angular velocity)

//    }

//    align_radius = 700; // for adjusting robot desired speed
//    for(int i=0; i<trajec.length(); i++) {
//        RRTVertex* node = trajec.getVertex(i);
//        float MDTG = goal.minDistTo(node->state); // min dist to goal
//        if(MDTG > align_radius) {
////            node->state.velo = node->state.velo.dotProduct(agent.velocity_limit);
//        }
//        else { // in the align velocity circle
//            float omega = node->state.velo.Teta();
//            node->state.velo = node->state.velo * (MDTG)/align_radius;
//            node->state.velo.setTeta(omega);
//        }
//    }
}

void PlanningProblem::solveInvalidInitialState()
{    
    cerr << "Warning: the initial state is drawn in an obstacle" << endl;
    for(uint i=0; i < stat_obstacles.size(); i++)  {
        Obstacle* ob = stat_obstacles[i];
        if(ob==NULL)  continue;
        if(hasCollision(initialState, *ob)) {
            Vector2D diff_to_ob(initialState.getPosition().to2D() - Vector2D(ob->m_transform.p));
            diff_to_ob.normalize();
            Station new_station;
            new_station.setPosition(initialState.getPosition() + (diff_to_ob * ob->shape->m_radius).to3D());
            trajec.clear();
            trajec.appendState(initialState);
            trajec.appendState(new_station);
            trajec.printToStream(cout);
            planningResult = true;
            return;
        }
    }

}

void PlanningProblem::solveInvalidGoalState()
{
    // TODO : make a strategy for handling this situation
    // strategy is to just displace goal point temporally to a valid point
    for(uint i=0; i<stat_obstacles.size(); i++) {
        Obstacle* ob = stat_obstacles[i];
        if(ob == NULL) continue;
        if(hasCollision(goal.goal_point, *ob)) {
            Vector2D diff = goal.goal_point.getPosition().to2D() - Vector2D(ob->m_transform.p);
            float displacement_ = agent.radius() + ob->shape->m_radius - diff.lenght();
            if(displacement_ > 0)
                goal.goal_point.setPosition( goal.goal_point.getPosition() +
                                             (diff.normalized() * displacement_ * 1.1).to3D());
            break;
        }
    }
}

bool PlanningProblem::checkPlanValidity(Trajectory &plan, float tolerance_coeff)
{
    if(plan.length() == 0)
        return false;
    if(Station::euclideanDistance(plan.getStation(0), initialState) > tolerance_coeff* agent.radius())
        return false;    
    if(goal.minDistTo(plan.getLastStation()) > tolerance_coeff * agent.radius())
        return false;
    if(Station::euclideanDistance(plan.getLastStation(), goal.goal_point) > tolerance_coeff * agent.radius() )
        return false;
//    for(int i=0; i<plan.length(); i++) {
//        if(!CheckValidity(plan.getStation(i)))
//            return false;
//    }
    return true;
}

//float PlanningProblem::EucleadianDistance(const Station &A, const Station &B)
//{
//    return (B.getPosition() - A.getPosition()).lenght2D();
//}

bool PlanningProblem::hasCollision(Station &st, const ObstacleSet &ob_set)
{
    b2Transform st_ateTransform;
    st_ateTransform.Set(st.getPosition().to2D().toB2vec2(), st.getPosition().Teta());

    for(unsigned int i=0; i<ob_set.size(); i++)
    {
        Obstacle* ob = ob_set[i];
        if(ob == NULL)
            continue;
        bool result = b2TestOverlap(ob->shape, 0, agent.shape, 1, ob->m_transform, st_ateTransform);
        if(result)
        {
//            std::cout << "collision with obstacle " << i << endl;
            return true;
        }
    }
    return false;
}

bool PlanningProblem::hasCollision(Station &st, const Obstacle &ob)
{
    b2Transform st_Transform;
    st_Transform.Set(st.getPosition().to2D().toB2vec2(), st.getPosition().Teta());

    return b2TestOverlap(ob.shape, 0, agent.shape, 1, ob.m_transform, st_Transform);
}

bool PlanningProblem::pathHasCollision(Station &from, Station &to, const ObstacleSet &ob_set)
{
    b2PolygonShape road_from_to;
    Vector2D center((from.getPosition() + to.getPosition()).to2D() /2.0);
    Vector2D half_diff((to.getPosition() - from.getPosition()).to2D() /2.0);
    float safet_latera_bound = 0.1;
    road_from_to.SetAsBox(agent.radius() * (1 + safet_latera_bound), half_diff.lenght() + agent.radius(),
                          center.toB2vec2(), M_PI_2 + half_diff.arctan());

    for(unsigned int i=0; i<ob_set.size(); i++)
    {
        Obstacle* ob = ob_set[i];
        if(ob == NULL)
            continue;
        bool result = b2TestOverlap(ob->shape, 0, &road_from_to, 1, ob->m_transform, identity_trans);
        if(result)
        {
            std::cout << "collision with obstacle " << i << endl;
            return true;
        }
    }
    return false;
}

bool PlanningProblem::pathHasCollision(Station &from, Station &to, const Obstacle &ob)
{
    b2PolygonShape road_from_to;
    Vector2D center((from.getPosition() + to.getPosition()).to2D() /2.0);
    Vector2D half_diff((to.getPosition() - from.getPosition()).to2D() /2.0);
    float safet_latera_bound = 0.1;
    road_from_to.SetAsBox(agent.radius() * (1 + safet_latera_bound), half_diff.lenght() + agent.radius(),
                          center.toB2vec2(), M_PI_2 + half_diff.arctan());

//    if(ob == NULL)
//        continue;
    return b2TestOverlap(ob.shape, 0, &road_from_to, 1, ob.m_transform, identity_trans);
}

// this function returns -1 if two objects has collision
// And otherwise returns the distance
float PlanningProblem::distToObstacle(Station A, const Obstacle &ob, b2Vec2& A_point, b2Vec2& ob_point)
{        
    b2DistanceProxy state_proxy, ob_proxy;
    state_proxy.Set(agent.shape, 0);
    ob_proxy.Set(ob.shape, 1);
    b2DistanceInput dist_in;
    dist_in.proxyA = state_proxy;
    dist_in.proxyB = ob_proxy;
    dist_in.transformA = b2Transform(A.getPosition().toB2vec2(),
                                    b2Rot(A.getPosition().Teta()));
    dist_in.transformB = ob.m_transform;
    b2SimplexCache dist_cache;
    dist_cache.count = 0;
    b2DistanceOutput dis_out;
    b2Distance(&dis_out, &dist_cache, &dist_in);
    A_point = dis_out.pointA;
    ob_point = dis_out.pointB;    
    if(hasCollision(A, ob)) {
        return -1;
    }
    return dis_out.distance;
}


Obstacle *PlanningProblem::nearestObstacle(Station A, const ObstacleSet &obset, float& dist, b2Vec2& A_point, b2Vec2& ob_point)
{
    Obstacle* res_ob = NULL;
    float min_dist = INFINITY;
    for (int i=0; i<obset.size(); i++) {
        float tmp_dist = distToObstacle(A, *obset[i], A_point, ob_point);
        if(tmp_dist < min_dist) {
            min_dist = tmp_dist;
            res_ob = obset[i];
        }
    }
    dist = min_dist;
    return res_ob;
}

bool PlanningProblem::CheckValidity(Station A)
{
    if(hasCollision(A, this->stat_obstacles))
        return false;
    if(hasCollision(A, this->dyna_obstacles))
        return false;
    return true;
}

Station PlanningProblem::SampleState()
{
    if(search_diameter > 0) {
        Ellipse el_1;
        el_1.m_center1 = initialState.getPosition().to2D();
        el_1.m_center2 = goal.goal_point.getPosition().to2D();
        el_1.m_diameter = search_diameter;
        return SampleStateInEllipse(el_1);
    }
    else
        return SampleStateUniform();
}

Station PlanningProblem::SampleStateUniform()
{
    float rt = uni_rand(0, M_2_PI);
    Station temp_station;
    for(int i=0; i < MAX_SAMPLING_TRY; ++i)
    {
        float rx = uni_rand(actualBound.getDownLeft().X(), actualBound.getTopRight().X());
        float ry = uni_rand(actualBound.getDownLeft().Y(), actualBound.getTopRight().Y());
        temp_station.setPosition(Vector3D(rx, ry, rt));
        if(CheckValidity(temp_station))
            return temp_station;
    }
    return Station();
}

Station PlanningProblem::SampleStateInEllipse(const Ellipse &ell_)
{
    float rt = uni_rand(0, M_2_PI);
    Station temp_station;
    for(int i=0; i < MAX_SAMPLING_TRY; ++i)
    {
        float rnd_rad = uni_rand(0, 1);
        float rnd_ang = uni_rand(0, 2 * M_PI);

        Vector2D cntr_disp(rnd_rad* cos(rnd_ang), rnd_rad* sin(rnd_ang));
        cntr_disp.rotate(ell_.orientation());

        Vector2D pnt = ell_.mainCenter() + cntr_disp;
        temp_station.setPosition(Vector3D(pnt, rt));
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

void PlanningProblem::computeCost(Trajectory &plan_)
{
    if(!this->checkPlanValidity(plan_)) {
        plan_.cost.safety = INFINITY;
        plan_.cost.smoothness = INFINITY;
        plan_.cost.length = INFINITY;
    }
    else {
        plan_.computeCost();
        plan_.cost.safety = 0;
        ObstacleSet desired_ob_set = stat_obstacles;
        desired_ob_set.insert(desired_ob_set.end(), dyna_obstacles.begin(), dyna_obstacles.end());
        for(int i=0; i< plan_.length(); i++) {
            Station st = plan_.getStation(i);
            float min_dist = INFINITY;
            b2Vec2 tmpv1, tmpv2;
            for(int j=0; j<desired_ob_set.size(); j++) {
                Obstacle* ob = desired_ob_set[j];
                float dist_ = distToObstacle(st, *ob, tmpv1, tmpv2);
                min_dist = min(min_dist, dist_);
            }
            st.cost.min_ob_dist = min_dist;
            plan_.EditStation(i, st);
            plan_.cost.safety += plan_.getStation(i).cost.safety_penalty();
        }
    }
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

void PlanningProblem::setPenaltyWeights(Trajectory::PlanCost cost_weights)
{
    computeCost(bestPlan);
    Trajectory::cost_weights = cost_weights;
}

Trajectory::PlanCost PlanningProblem::getPenaltyWeights() const
{
    return Trajectory::cost_weights;
}

void PlanningProblem::setGoalPoint(Station st)
{
    this->goal.goal_point.set(st);
}

void PlanningProblem::setBound(FieldBound fb)
{
    this->actualBound = fb;
}

FieldBound PlanningProblem::getBound() const
{
    return this->actualBound;
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

ObstacleSet PlanningProblem::getDynamicObstacles() const
{
    return this->dyna_obstacles;
}

void PlanningProblem::clearObstacles(bool dynamix, bool statix)
{
    if(statix) {
        for(int i=stat_obstacles.size()-1; i>=0; i--)
        {
            Obstacle* ob = (Obstacle*)stat_obstacles[i];
            if(ob != NULL)
                delete ob;
        }

        this->stat_obstacles.clear();
    }

    if(dynamix) {
        for(int i=dyna_obstacles.size()-1; i>=0; i--)
        {
            Obstacle* ob = (Obstacle*)dyna_obstacles[i];
            if(ob != NULL)
                delete ob;
        }
        this->dyna_obstacles.clear();
    }

}

RandomTree& PlanningProblem::getTree()
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
    if(i < trajec.length()) {
        Station st = trajec.getStation(i);
        c = st.getVelocity();
    }
    else
        c.setZero();
    return c;
}

Velocity PlanningProblem::getNextControl(Trajectory tr_)
{
    Velocity vel_;
    if(checkPlanValidity(tr_)) {
        Station next_st = tr_.getStation(1);
        Vector3D delta_pos = next_st.getPosition() - initialState.getPosition();
        double delta_orien = delta_pos.to2D().arctan() - initialState.getPosition().Teta();
        delta_orien = continuousRadian(delta_orien, -M_PI);
        Vector2D v_2d = Vector2D::unitVector(delta_orien);
        v_2d = v_2d / (fabs(delta_orien) + 0.5);
        vel_.set(v_2d.X(), v_2d.Y(), 0);
    }
    else
        vel_.setZero();
    return vel_;
}

Trajectory PlanningProblem::getPlan()
{
    return bestPlan;
}
