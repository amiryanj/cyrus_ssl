#include "planningproblem.h"
#include <Box2D/Collision/b2Distance.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <iostream>
#include "../../../shared/utility/generalmath.h"
#include "../../../shared/utility/randomsampling.h"
//#include "../GA/planningchromosom.h"

PlanningProblem* PlanningProblem::instance = NULL;

PlanningProblem *PlanningProblem::getInstance()
{
    if(instance == NULL)
        instance = new PlanningProblem();
    return instance;
}

PlanningProblem::PlanningProblem() {
    identity_trans.SetIdentity();
    actualBound = NULL;
}

bool PlanningProblem::solve()
{
    double start_time = currentTimeMSec();
    planningResult = false;

    if (!CheckValidity(goal.goal_point)) {
        cerr << "Warning: the Goal state is drawn in an obstacle" << endl;
        solveInvalidGoalState();
    }

//    if(goal.minDistTo(initialState) == 0) { // if it is already in the goal region
//        trajec.clear();
//        planningResult = true;
//    }
//    else if(!CheckValidity(initialState))
//        solveInvalidInitialState();

//    else
    {  // normal way of solvgin motion planning problem
        ObstacleSet desired_ob_set = stat_obstacles;
        Trajectory apft_ = APFSolve(desired_ob_set, false);
        Trajectory pt_ = PruneTrajectory(apft_, desired_ob_set);
//        delete apft_;
        trajec.copyFrom(pt_);
//        if(!planningResult) {
//            GRRTsolve();
//            buildTrajectoryFromTree();
//        }
//        if(!planningResult) {
//            RRTsolve();
//        }

        if(planningResult) {
            if(goal.minDistTo(trajec.getLastStation()) > agent->radius())
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
//    cout << "Planning Succeed in (ms): " << total_time << endl;
    return planningResult;
}

bool PlanningProblem::replan(const ObstacleSet &ob_set, Trajectory &trajec)
{
    if(trajec.length() < 2)
        return false;

    Vector2D goals_diff = (goal.goal_point.getPosition() - trajec.getLastStation().getPosition()).to2D();
    if(goals_diff.lenght() > agent->radius())
        return false;

    Vector2D inits_dist = (initialState.getPosition() - trajec.getFirstStation().getPosition()).to2D();
    if(inits_dist.lenght() > agent->radius())
        return false;

    trajec.EditStation(0, initialState);
    trajec.EditStation(trajec.length() -1, goal.goal_point);
    return true;
}

vector<Vector2D> PlanningProblem::ObstacleForces(const Station &st, const ObstacleSet &ob_set)
{
    vector<Vector2D> ob_force_list;
    ob_force_list.reserve(ob_set.size());

    float extension_len = agent->radius();
    for(uint i=0; i<ob_set.size(); i++) {
        const Obstacle* ob = ob_set[i];
        b2Vec2 agent_colid_pnt, ob_collid_pnt;
        float dist_to_ob = distToObstacle(st, *ob, agent_colid_pnt, ob_collid_pnt);
        if(dist_to_ob > extension_len * 10)   // ignore it
            continue;
        Vector2D ob_force;
        float repulse_strenght_by_dist = min(extension_len /fabs(dist_to_ob), 1.099f);
        if(dist_to_ob < 0)  // in collision state
            ob_force = (st.getPosition().to2D() - ob->CenterOfMass()).normalized();
        else
            ob_force = Vector2D(agent_colid_pnt - ob_collid_pnt).normalized();
        ob_force *= ob->repulseStrenght * repulse_strenght_by_dist * 1.1;
        ob_force_list.push_back(ob_force);
    }
    return ob_force_list;
}

Vector2D PlanningProblem::PathDirectedForce(const Station &st, Trajectory &path_)
{
    Station sub_goal = getNextStation(st, path_);

    return (sub_goal.getPosition().to2D() - st.getPosition().to2D()).normalized() * 1.0;
}

Station PlanningProblem::getNextStation(const Station &st, Trajectory &path)
{
    if(path.isEmpty())
        return this->goal.goal_point;
    if(path.length() <= 2)
        return path.getLastStation();

    float max_memberance = 0;
    int nearest_segment_index = -1;
    for(uint i=1; i<path.length(); i++) { // it doesnt use the last segment (go towards goal on last segment)
        Vector2D pnt_1 = path.getStation(i-1).getPosition().to2D();
        Vector2D pnt_2 = path.getStation(i).getPosition().to2D();

        float dist_st_segment = (st.getPosition().to2D() - pnt_1).lenght() +
                                                (st.getPosition().to2D() - pnt_2).lenght();
        float segment_len = (pnt_1 - pnt_2).lenght();

        float segment_mem = segment_len /dist_st_segment;
        if(segment_mem > max_memberance) {
            max_memberance = segment_mem;
            nearest_segment_index = i;
        }
    }

    return path.getStation(nearest_segment_index);
}

Vector2D PlanningProblem::GoalAttractiveForce(const Station &st)
{
    Vector2D diff_to_goal = (goal.goal_point.getPosition() - st.getPosition()).to2D();
    double stren = 1.5 * tanh(diff_to_goal.lenght()/25.0) + 0.1;
    return diff_to_goal.normalized() * stren;
}

Trajectory PlanningProblem::APFSolve(const ObstacleSet &ob_set, bool stop_when_collid)
{
    Trajectory empty_trajec;
    return RRT_APF_Solve(ob_set, empty_trajec, stop_when_collid);
}

Trajectory PlanningProblem::RRT_APF_Solve(const ObstacleSet &ob_set,
                                           Trajectory &prior_plan,
                                           bool stop_when_collid)
{
    Trajectory *temp_trajec = new Trajectory();
    temp_trajec->appendState(initialState);

    for(int step = 1; step <= MAX_APF_STEP_TRY; step++) {
        // check reaching the goal state
        Station current_station = temp_trajec->getLastStation();
        if( (goal.minDistTo(current_station) < agent->radius() * 1) )
        {
            temp_trajec->appendState(goal.goal_point);
            planningResult = true;
            break;
        }

        Vector2D total_force;
        if( !pathHasCollision(current_station, goal.goal_point, ob_set) ) {
//            temp_trajec->appendState(goal.goal_point);
//            planningResult = true;
//            break;
            total_force += GoalAttractiveForce(current_station);
        }

//        else
        {
            Station next_goal = getNextStation(current_station, prior_plan);
            total_force += PathDirectedForce(current_station, prior_plan);
            vector<Vector2D> ob_forces = ObstacleForces(current_station, ob_set);
            Vector2D ob_total_force;
            for(uint i=0; i<ob_forces.size(); i++)  {
                ob_total_force += ob_forces[i];
            }
            if(!pathHasCollision(current_station, next_goal, ob_set)) {
                ob_total_force *= 0.2;
            }
            total_force += ob_total_force;
        }

        Station new_station;
        new_station = agent->step(current_station,
                                  (total_force.normalized()).to3D(),
                                  0.080 /*sec*/);
        temp_trajec->appendState(new_station);
        if(stop_when_collid) {
            if( !CheckValidity(new_station) ) {
                planningResult = false;
                break;
            }
        }
    }
    return *temp_trajec;
}

Trajectory PlanningProblem::GRRTsolve()
{
    this->planningResult = false;
    randomTree.clear();
    float start_time = currentTimeMSec();
    int tryExtensionCounter = 0;
    randomTree.appendNewStation(NULL, initialState);

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
        SpatialVertex* near_ver = randomTree.getNearestVertex(target);
        if(near_ver == NULL)
            continue;

        int greedyCounter = 0;
        while(greedyCounter < 5){
            tryExtensionCounter ++;
            Station extended = RRTExtend(near_ver->state, target, agent->radius() * 2);
            if(!extended.isValid())
                break;
            randomTree.appendNewStation(near_ver, extended);
            if(Station::dubinDistance(extended, target) < agent->radius() ) {
                if((target.getPosition() - goal.goal_point.getPosition()).lenght2D() < agent->radius() /2)
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
        float finish_time = currentTimeMSec();
        this->planningTime = finish_time - start_time;
//        cout << "Greedy RRT Planning succeed in " << planningTime << "mili seconds" << endl;
        return buildTrajectoryFromRandomTree();
    }
    return Trajectory();
}

// *************************************************
// ************** under construction ***************
// *************************************************
Trajectory PlanningProblem::RRTConnectSolve(double arg1)
{
    double start_time = currentTimeMSec();
    randomTree.clear();
    backward_tree.clear();
    randomTree.appendNewStation(NULL, initialState);
    backward_tree.appendNewStation(NULL, goal.goal_point);

    for(uint i=0; i< MAX_RRT_STEP_TRY ; ++i)
    {
        Station randSt = SampleStateUniform();
        if(!randSt.isValid())
            continue;
        SpatialVertex* near_ver = randomTree.getNearestVertex(randSt);
        if(near_ver == NULL)
            continue;
        Station extended_ = RRTExtend(near_ver->state, randSt, arg1);
        if(!extended_.isValid())
            continue;
        randomTree.appendNewStation(near_ver, extended_);

        for(int j=0; j<10; j++) {
            SpatialVertex* back_near = backward_tree.getNearestVertex(extended_);
            Station back_extended = RRTExtend(back_near->state, extended_, arg1);
            if(!back_extended.isValid())
                break;
            backward_tree.appendNewStation(back_near, back_extended);

            if(Station::euclideanDistance(back_extended, extended_) < agent->radius()) {
                while(back_near != NULL) {
                    Station on_back_tree_st = back_near->state;
                    on_back_tree_st.setPosition(Vector3D(back_near->state.getPosition().to2D(),
                                                         back_near->state.getPosition().Teta() + M_PI));
                    randomTree.appendNewStation(randomTree.lastAddedVertex(), on_back_tree_st);
                    back_near = back_near->parent;
                }
                planningTime = currentTimeMSec() - start_time;
                return buildTrajectoryFromRandomTree();
            }
        }
    }
    planningTime = currentTimeMSec() - start_time;
    return Trajectory();
}

void PlanningProblem::deactivate()
{
    this->trajec.clear();
    this->randomTree.clear();
}

Trajectory PlanningProblem::PruneTrajectory(Trajectory &input_plan, const ObstacleSet& ob_set)
{
    if(input_plan.length() < 3)
        return input_plan;

    Trajectory prunned_plan;
    int st_index = 1;
    prunned_plan.appendState(input_plan.getStation(0));
    while((input_plan.length() - st_index) > 1) {
        Station st_A = prunned_plan.getLastStation();
        Station st_B = input_plan.getStation(st_index +1);
        if(pathHasCollision(st_A, st_B, ob_set)) {
            Station new_inserted_st = input_plan.getStation(st_index);
            float new_teta = (new_inserted_st.getPosition().to2D() -
                              prunned_plan.getLastStation().getPosition().to2D()).arctan();
            new_inserted_st.setPosition(Vector3D(new_inserted_st.getPosition().to2D(), new_teta));
            prunned_plan.appendState(new_inserted_st);
        }
        st_index ++;
    }
    prunned_plan.appendState(input_plan.getLastStation());
    return prunned_plan;
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
//        if(ob_ != NULL && min_dist_to_ob < agent->radius() * 1.5) {
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

Trajectory PlanningProblem::RRTsolve(float arg1, float max_len)
{
//    if(tree.count() > MAX_TREE_SIZE * 0.75)
    randomTree.clear();
       this->planningResult = false;

   double start_time = currentTimeMSec();
   randomTree.appendNewStation(NULL, initialState);
   for(uint i=0; i< MAX_RRT_STEP_TRY ; ++i)
   {
       if(RRTStep(arg1, max_len) == eReached)
       {
           this->planningResult = true;
           double finish_time = currentTimeMSec();
           this->planningTime = finish_time - start_time;
           return buildTrajectoryFromRandomTree();
           break;
       }
   }
   return Trajectory();
}

Station PlanningProblem::RRTExtend(const Station &start, const Station &target, float extension_len)
{
    Vector3D diff_vec = target.getPosition() - start.getPosition();
    diff_vec.normalize2D();
    diff_vec *= extension_len;
    float start_angle = start.getPosition().Teta();
    start_angle = continuousRadian(start_angle, diff_vec.to2D().arctan() - M_PI);
    float rotate_angle = (diff_vec.to2D().arctan() - start_angle) / 1.5;

    diff_vec.setTeta(rotate_angle);
    Station temp_station;
    temp_station.setPosition((diff_vec + start.getPosition()).standardizeTeta());
    bool valid = CheckValidity(temp_station);
    if(valid)
        return temp_station;
    return Station();
}

PlanningProblem::ExtendResult PlanningProblem::RRTStep(float extension_len, float max_len)
{
    ExtendResult result;
    try {
        Station rand_st;
        float toss = uni_rand(0, 1);
        if(toss < GOAL_PROB)
            rand_st.set(goal.goal_point);
        else
        {
            if(max_len < INFINITY) {
                Vector2D rand_point = randomSampleFromEllipse(initialState.getPosition().to2D(),
                                                              goal.goal_point.getPosition().to2D(),
                                                              max_len);
                Station temp;
                temp.setPosition(Vector3D(rand_point, uni_rand(-M_PI, M_PI)));
                rand_st.set(temp);

            }
            else {
                Station temp = SampleStateUniform();
                rand_st.set(temp);
            }
        }

        if(!rand_st.isValid())
            throw "can not sampled!";
        SpatialVertex* near_ver = randomTree.getNearestVertex(rand_st);

        //    if(near_ver->state.isValid())
        if(near_ver == NULL)
            throw "can not find nearest!";

        Station new_st = RRTExtend((near_ver->state), rand_st, extension_len);
        if(!new_st.isValid())
        {
            result = eTrapped;
            throw "can not extend tree!";
        }
        if(goal.minDistTo(new_st) < agent->radius() * 1)
            result = eReached;
        else
            result = eAdvanced;
        randomTree.appendNewStation(near_ver, new_st);

    } catch (const char* msg)
    {
//        cerr << "Exception in RRTStep: " << msg << endl;
    }
    return result;
}

Trajectory PlanningProblem::buildTrajectoryFromRandomTree()
{
    Trajectory temp_trajec;

    // build path (in backward direction)
    SpatialVertex* last_vertex = randomTree.getNearestVertex(goal.goal_point);
    temp_trajec.appendState(last_vertex->state);

    SpatialVertex* parent = last_vertex->parent;
    while (parent != NULL) {
        temp_trajec.prependState(parent->state);
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
//        float min_reach_time = 2.2 * dist_to_parent / agent->velocity_limit.to2D().lenght();
//        float rotate_val;
//        float MDTG = goal.minDistTo(current_node->state); // min dist to goal
//        if(MDTG > align_radius) {
//            float d_teta_a = SSL::minAngleDistToRange(parent->state.position.Teta(),
//                                        current_node->state.velo.to2D().arctan(), current_node->state.velo.to2D().arctan());
//            float d_teta_b = SSL::minAngleDistToRange(parent->state.position.Teta(),
//                                        M_PI+current_node->state.velo.to2D().arctan(), M_PI+current_node->state.velo.to2D().arctan());
//            float d_teta = (fabs(d_teta_a) < fabs(d_teta_b))? d_teta_a:d_teta_b;
//            assert(fabs(d_teta) < M_PI);
//            rotate_val = agent->velocity_limit.Teta() * min_reach_time * sin(d_teta/2);
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
////            node->state.velo = node->state.velo.dotProduct(agent->velocity_limit);
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
            Vector2D diff_to_ob(initialState.getPosition().to2D() - Vector2D(ob->transform.p));
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
            Vector2D diff = goal.goal_point.getPosition().to2D() - Vector2D(ob->transform.p);
            float displacement_ = agent->radius() + ob->shape->m_radius - diff.lenght();
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
    if(Station::euclideanDistance(plan.getStation(0), initialState) > tolerance_coeff* agent->radius())
        return false;    
    if(goal.minDistTo(plan.getLastStation()) > tolerance_coeff * agent->radius())
        return false;
    if(Station::euclideanDistance(plan.getLastStation(), goal.goal_point) > tolerance_coeff * agent->radius() )
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

bool PlanningProblem::hasCollision(const Station &st, const ObstacleSet &ob_set)
{
    b2Transform stateTransform;
    stateTransform.Set(st.getPosition().to2D().toB2vec2(), st.getPosition().Teta());

    for(unsigned int i=0; i<ob_set.size(); i++)
    {
        Obstacle* ob = ob_set[i];
        if(ob == NULL)
            continue;
        bool result = b2TestOverlap(ob->shape, 0, agent->shape, 1, ob->transform, stateTransform);
        if(result)
        {
//            std::cout << "collision with obstacle " << i << endl;
            return true;
        }
    }
    return false;
}

bool PlanningProblem::hasCollision(const Station &st, const Obstacle &ob)
{
    b2Transform st_Transform;
    st_Transform.Set(st.getPosition().to2D().toB2vec2(), st.getPosition().Teta());

    return b2TestOverlap(ob.shape, 0, agent->shape, 1, ob.predictedTransform(0), st_Transform);
}

bool PlanningProblem::pathHasCollision(const Station &from, const Station &to, const ObstacleSet &ob_set)
{
    b2PolygonShape road_from_to;
    Vector2D center((from.getPosition() + to.getPosition()).to2D() /2.0);
    Vector2D half_diff((to.getPosition() - from.getPosition()).to2D() /2.0);
    float safety_lateral_bound = -0.20;
    road_from_to.SetAsBox(agent->radius() * (1 + safety_lateral_bound),
                          half_diff.lenght() + agent->radius() * (1+safety_lateral_bound),
                          center.toB2vec2(), M_PI_2 + half_diff.arctan());

    for(unsigned int i=0; i<ob_set.size(); i++)
    {
        Obstacle* ob = ob_set[i];
        if(ob == NULL)
            continue;
        bool result = b2TestOverlap(ob->shape, 0, &road_from_to, 1, ob->transform, identity_trans);
        if(result)
        {
//            std::cout << "collision with obstacle " << i << endl;
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
    road_from_to.SetAsBox(agent->radius() * (1 + safet_latera_bound), half_diff.lenght() + agent->radius(),
                          center.toB2vec2(), M_PI_2 + half_diff.arctan());

//    if(ob == NULL)
//        continue;
    return b2TestOverlap(ob.shape, 0, &road_from_to, 1, ob.transform, identity_trans);
}

// this function returns -1 if two objects has collision
// And otherwise returns the distance
float PlanningProblem::distToObstacle(Station A, const Obstacle &ob, b2Vec2& A_point, b2Vec2& ob_point)
{        
    b2DistanceProxy state_proxy, ob_proxy;
    state_proxy.Set(agent->shape, 0);
    ob_proxy.Set(ob.shape, 1);
    b2DistanceInput dist_in;
    dist_in.proxyA = state_proxy;
    dist_in.proxyB = ob_proxy;
    dist_in.transformA = b2Transform(A.getPosition().toB2vec2(),
                                    b2Rot(A.getPosition().Teta()));
    dist_in.transformB = ob.transform;
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


Obstacle *PlanningProblem::nearestObstacle(const Station &A, const ObstacleSet &obset,
                                           float& dist, b2Vec2& A_point, b2Vec2& ob_point)
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

bool PlanningProblem::CheckValidity(const Station &A)
{
    return ( ! hasCollision(A, this->stat_obstacles) );
}

Station PlanningProblem::SampleStateUniform()
{
    Station sampled_station;
    for(int i=0; i < MAX_SAMPLING_TRY; ++i)
    {
        Vector3D rand_pos = actualBound->getUniformSample();
        sampled_station.setPosition(rand_pos);
        if(CheckValidity(sampled_station))
            return sampled_station;
    }
    return Station();
}

void PlanningProblem::setPlanningAgent(PlanningAgent *ag)
{
    this->agent = ag;
}

PlanningAgent* PlanningProblem::getPlanningAgent() const
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
        for(int i=0; i< plan_.length(); i++) {
            Station st = plan_.getStation(i);
            float min_dist = INFINITY;
            b2Vec2 tmpv1, tmpv2;
            for(int j=0; j<desired_ob_set.size(); j++) {
                Obstacle* ob = desired_ob_set[j];
                float dist_ = distToObstacle(st, *ob, tmpv1, tmpv2);
                min_dist = min(min_dist, dist_);
            }
            st.cost.min_dist_to_obs = min_dist;
            plan_.EditStation(i, st);
            plan_.cost.safety += plan_.getStation(i).cost.safety_penalty() / plan_.length();
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

void PlanningProblem::setBound(FieldBound* fb)
{
    this->actualBound = fb;
}

FieldBound* PlanningProblem::getBound() const
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

void PlanningProblem::clearObstacles()
{
    for(int i=stat_obstacles.size()-1; i>=0; i--)
    {
        Obstacle* ob = (Obstacle*)stat_obstacles[i];
        if(ob != NULL)
            delete ob;
    }

    this->stat_obstacles.clear();
}

SpatialTree& PlanningProblem::getTree()
{
    return randomTree;
}

Trajectory PlanningProblem::getTrajectory() const
{
    return trajec;
}

Velocity PlanningProblem::getControl(uint i)
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

Trajectory PlanningProblem::getBestPlan()
{
    return bestPlan;
}

Station PlanningProblem::getFirstSubGoal()
{
    Station st;
    if( trajec.length() > 1 )   {
        st = trajec.getStation(1);
    }
    return st;
}
