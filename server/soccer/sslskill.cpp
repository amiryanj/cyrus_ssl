#include "sslskill.h"
#include "../ai/SSLWorldModel.h"
#include "../ai/SSLAnalyzer.h"
#include "../definition/SSLBall.h"
#include "../definition/SSLRobot.h"
#include "../transmitter/RobotCommandPacket.h"
#include "../transmitter/commandtransmitter.h"
#include "sslrole.h"
#include "sslagent.h"
#include "sslgamepositions.h"
#include "../paramater-manager/parametermanager.h"
#include "../log-tools/logger.h"
#include "../log-tools/networkplotter.h"

Vector3D SSLSkill::defaultTolerance;

SSLSkill::SSLSkill(SSLAgent *parent)
{
    ParameterManager* pm = ParameterManager::getInstance();

    this->owner_agent = parent;
    defaultTolerance.setX(   pm->get<float>("skills.default_tolerance.x")    );
    defaultTolerance.setY(   pm->get<float>("skills.default_tolerance.y")    );
    defaultTolerance.setTeta(pm->get<float>("skills.default_tolerance.teta_deg")*M_PI/180.0);

    initializePlanner();
}

void SSLSkill::halt()
{
    this->name = "Halt";

    Vector3D zeroSpeed(0, 0, 0);
    controlSpeed(zeroSpeed, false);
}

// go to the final target of the robot
// in this case the orientation should be token into account
void SSLSkill::goToPoint(Vector3D target, const Vector3D &tolerance)
{
    this->name = "Goto target";
    this->target = target;
    planner.deactive();

    Vector3D diff = target - this->Position();
    if(       ( fabs(diff.X())    < tolerance.X() )
           && ( fabs(diff.Y())    < tolerance.Y() )
           && ( fabs(diff.Teta()) < tolerance.Teta() ) )
    {
        Vector3D zeroSpeed(0.0, 0.0, 0.0);
        controlSpeed(zeroSpeed, false);
    }
    else {
        goToSubGoal(target, tolerance);
    }
}

void SSLSkill::goToPoint(Vector3D target)
{
    goToPoint(target, this->defaultTolerance);
}

void SSLSkill::goToPoint(Vector2D target, const Vector2D &tolerance)
{
    Vector3D target_with_set_orien(target, (target - Position().to2D()).arctan());
    goToPoint(target_with_set_orien, Vector3D(tolerance, defaultTolerance.Teta()));
}

void SSLSkill::goToPoint(Vector2D target)
{
    goToPoint(target, this->defaultTolerance.to2D());
}

void SSLSkill::goToSubGoal(const Vector3D &target, const Vector3D &tolerance)
{
    Vector3D target2;

    double thr1 = ParameterManager::getInstance()->get<double>("skills.thr1");
    double thr2 = ParameterManager::getInstance()->get<double>("skills.thr2");
    Vector3D diff = target - this->Position();

    if(diff.lenght2D() > thr1)
    {
        diff.normalize2D();
        target2 = this->Position() + diff*thr2;
        target2.setTeta(diff.to2D().arctan());
//            this->planner.trajec.prependState(Station(target2));
        move(this->Position(), target2, tolerance, 1.0);

    }  else
    {
        move(this->Position(), target, tolerance);
    }
}

void SSLSkill::goToPointWithPlanner(const Vector3D &target, const Vector3D &tolerance,
                                    bool considerPenaltyArea,
                                    float ball_obs_radius, float robot_obs_radius)
{
    this->name = "Plan and go to point";
    this->target = target;

    Station init_state;
    init_state.setPosition(this->Position());
    init_state.setVelocity(owner_agent->robot->Speed());
    planner.setInitialState(init_state);

    GoalState goal;
    goal.goal_point.setPosition(target);
    goal.tolerance.setPosition(tolerance);
    planner.setGoalRegion(goal);

    ObstacleSet allObstacles;
    allObstacles.reserve(2*MAX_ID_NUM + 6);

    if(considerPenaltyArea)    {// for all robots except goal keeper
        // insert all static obstacles related to penalty area
        allObstacles.insert(allObstacles.begin(),
                            penaltyAreaObstacles.begin(), penaltyAreaObstacles.end());
    }

    // update position of obstacles
    if(robot_obs_radius != 0)  {
        vector<SSLRobot* > all_actual_robots = SSLWorldModel::getInstance()->getInFieldRobotsExcept(owner_agent->robot);
        for(uint i =0; i<all_actual_robots.size(); i++)
        {
            SSLRobot* rob_ = all_actual_robots[i];
            Obstacle* ob_  = allRobotsObstacles[i];
            ob_->shape->m_radius = robot_obs_radius;
            ob_->m_transform.Set(Vector2D(rob_->Position().X(), rob_->Position().Y()).toB2vec2(), rob_->Position().Teta());
            allObstacles.push_back(ob_);
        }
    }

    if(ball_obs_radius != 0) {
        ballObstacle->shape->m_radius = ball_obs_radius;
        allObstacles.push_back(ballObstacle);
    }

    planner.setStaticObstacles(allObstacles);

    // we dont need to run all planners in every frame
    if( (SSLGame::getInstance()->game_running_counter % MAX_ID_NUM) == owner_agent->getID())
        planner.solve();

    int plan_lenght = planner.getTrajectory().length();
    if( plan_lenght >1 )   {
        Station subGoal = planner.getTrajectory().getStation(1);
        if(plan_lenght > 2)   {
            Vector3D tolerance_without_orien = tolerance;
            tolerance_without_orien.setTeta(M_PI_2);
            this->goToSubGoal(subGoal.getPosition(), tolerance_without_orien);
        }   else   {
            this->goToSubGoal(subGoal.getPosition(), tolerance);
        }
    }


}

// this function is responsible for approaching the ball
// and setting the orientation such that it can kick the ball
// it should get the target to shoot
void SSLSkill::goAndKick(const Vector2D kick_point,const  Vector2D kick_target, float kickStrenghtNormal)
{
    this->name = "Kick ball";
//    planner.deactive();

    bool is_robot_behind_ball;
    {
    Vector2D ball_target_diff_vector(kick_target - kick_point);
    Vector2D prependicular_vector = Vector2D::unitVector(ball_target_diff_vector.arctan() + M_PI_2);
    LineSegment prependicular_line_to_ball_target_vec(kick_point + prependicular_vector * FIELD_WIDTH_2,
                                                      kick_point - prependicular_vector * FIELD_WIDTH_2);


    float dist_robot_and_ball_line = this->Position().to2D().distToLine(prependicular_line_to_ball_target_vec);
    Vector2D robot_kicker_device_point = this->Position().to2D() + Vector2D::unitVector(this->Position().Teta());

    is_robot_behind_ball =
            ( (Vector2D::dot((kick_point - kick_target), (robot_kicker_device_point - kick_point)) > 0)
              && (dist_robot_and_ball_line > (ROBOT_RADIUS + BALL_RADIUS)) );

    }

    float diff_len = (kick_point - this->Position().to2D()).lenght();

    if(analyzer->canKick(owner_agent->robot))  {
        planner.deactive();
        Vector3D speed(0.2, 0, 0); // go fast in forward direction to reach ball and then kick it
        CommandTransmitter::getInstance()->buildAndSendPacket(owner_agent->getID(), speed, kickStrenghtNormal);
    }
    else if(is_robot_behind_ball && (diff_len < 500))  {
        planner.deactive();
        Vector3D kick_ball_point = SSL::Position::KickStylePosition(kick_point, kick_target, -20);
        target = kick_ball_point;
        Vector3D tolerance(20, 20, M_PI/4.0);
        goToSubGoal(target, tolerance);
    }
    else {
        Vector3D behind_ball_target = SSL::Position::KickStylePosition(kick_point, kick_target, 100);
        Vector3D tolerance(ROBOT_RADIUS/2, ROBOT_RADIUS/2, M_PI/4.0);
        goToPointWithPlanner(behind_ball_target, tolerance, false, 0.7 * BALL_RADIUS, 0);
    }
}

void SSLSkill::goAndChip(double chipStrenghtNormal)
{
    this->name = "Chip ball";
    planner.deactive();
}

void SSLSkill::goBehindBall(Vector2D ball_position)
{
    assert(0);
}

double SSLSkill::computeVelocityStrenghtbyDistance(double dist , double max_speed)
{
    double stop_radius_A = 450 /*mili meter*/ ; // max_speed / 1.5;
    double stop_radius_B = 250 /*mili meter*/ ;
    double ratio = 1;
//    if(dist < stop_radius_B) {
//        ratio = (dist / stop_radius_B) * 0.4;
//        ratio = pow(ratio, 1.2);
//    }
//    else
        if(dist < stop_radius_A) {
        ratio = (dist / stop_radius_A);
    }
    ratio = pow(ratio, 1.5);

    ratio = bound(ratio , 0.12 , 1.0);
    return ratio;
}
void SSLSkill::move(const Vector3D &current_pos,
                    const Vector3D &target_pos,
                    const Vector3D &tolerance,
                    double speed_coeff)
{
    Vector3D diff = target_pos - current_pos;
    diff.setTeta(continuousRadian(diff.Teta(), -M_PI));


    double linear_vel_strenght;
    if(speed_coeff > 0)
        linear_vel_strenght = speed_coeff;
    else {
        linear_vel_strenght = computeVelocityStrenghtbyDistance(diff.lenght2D(),
                                                        owner_agent->robot->physic.max_lin_vel_mmps);
    }

    // set omega in different orientations
    float omega = 0;
    if ( fabs(diff.Teta()) > (2.0/3.0)*M_PI )  {
        omega = 0.22 * sgn(diff.Teta());
        linear_vel_strenght = std::min(0.25, linear_vel_strenght);
    }
    else if ( fabs(diff.Teta()) > (1.0/5.0)*M_PI ) {
        omega = 0.15 * sgn(diff.Teta());
        linear_vel_strenght = std::min(0.5, linear_vel_strenght);
    }
    else if ( fabs(diff.Teta()) > tolerance.Teta()) {
        omega = 0.12 * sgn(diff.Teta());
        linear_vel_strenght = std::min(0.65, linear_vel_strenght);
    }
    else {
        omega = 0;
    }

    float general_linear_coeff = 0.7;
    float general_omega_coeff  = 0.7;

    linear_vel_strenght *= general_linear_coeff;
//    NetworkPlotter::getInstance()->buildAndSendPacket("vel_strenght", linear_vel_strenght);

    const float robot_linear_max_speed = owner_agent->robot->physic.max_lin_vel_mmps;

    diff.normalize2D();
    Vector3D desired_gloabal_speed(diff.to2D().normalized().X() * linear_vel_strenght * robot_linear_max_speed,
                                   diff.to2D().normalized().Y() * linear_vel_strenght * robot_linear_max_speed,
                                   omega    * general_omega_coeff);

    controlSpeed(desired_gloabal_speed, true /*use controller*/);

    // send data to visualizer
//    {
//        vector<double> speed_to_sent;
//        vector<string> speed_labels;
//        speed_to_sent.push_back(desired_gloabal_speed.X());
//        speed_to_sent.push_back(desired_gloabal_speed.Y());
//        speed_to_sent.push_back(desired_gloabal_speed.Teta() * 1000.0);
//        speed_labels.push_back("X");
//        speed_labels.push_back("Y");
//        speed_labels.push_back("W");
//        NetworkPlotter::getInstance()->buildAndSendPacket("desired_speed", speed_to_sent, speed_labels);
//    }

}

void SSLSkill::controlSpeed(const Vector3D& desired_speed, bool use_controller)
{
    Vector3D actual_speed = this->owner_agent->robot->Speed();
    this->desiredGlobalSpeed = desired_speed;

    if(use_controller) {
        controller.setPoint(desired_speed, actual_speed);
        appliedGlobalSpeed = controller.getControl();
    }
    else {
        float max_speed = owner_agent->robot->physic.max_lin_vel_mmps;
        this->appliedGlobalSpeed = desiredGlobalSpeed ;
        this->appliedGlobalSpeed.setX(this->appliedGlobalSpeed.X() / max_speed);
        this->appliedGlobalSpeed.setY(this->appliedGlobalSpeed.Y() / max_speed);
    }

    Vector3D appliedLocalSpeed = appliedGlobalSpeed ;
    appliedLocalSpeed.rotate( -1 * Position().Teta());

    CommandTransmitter::getInstance()->buildAndSendPacket(owner_agent->getID(), appliedLocalSpeed);

    if(owner_agent->getID() == 2)
    {
        NetworkPlotter::getInstance()->buildAndSendPacket("omega", desiredGlobalSpeed.Teta());

        vector<double> speed_to_sent;
        vector<string> speed_labels;
        speed_to_sent.push_back(desiredGlobalSpeed.lenght2D());
        speed_labels.push_back("desire_len");
        speed_to_sent.push_back(owner_agent->robot->Speed().lenght2D());
        speed_labels.push_back("actual_len");
        speed_to_sent.push_back(this->controller.lastApplied.lenght2D() * 1000.0);
        speed_labels.push_back("applied_len");
        NetworkPlotter::getInstance()->buildAndSendPacket("control_y", speed_to_sent, speed_labels);
    }
}

void SSLSkill::initializePlanner()
{
    FieldBound bound;
    bound.set(-1.1 * FIELD_LENGTH/2, 1.1 * FIELD_LENGTH/2,
              -1.1 * FIELD_WIDTH /2, 1.1 * FIELD_WIDTH /2 );
    planner.setBound(bound);
    PlanningAgent planning_agent;
    planning_agent.motionModel = MP::eOmniDirectional;
    planning_agent.setRadius(ROBOT_RADIUS); // in milimeter
    planning_agent.mass = 3.0; // kilo gram
    planning_agent.velocity_limit.set(3000, 3000, M_PI * 1.2);
    planner.setPlanningAgent(planning_agent);

    // initializing field obstacles for agent
    // ****************************************************************************************
    penaltyAreaObstacles.reserve(5);
    int z = ParameterManager::getInstance()->get<int>("general.game.our_side");
    Obstacle* myPenaltyArea_C = new Obstacle(Obstacle::eStatic, b2Vec2(z* FIELD_LENGTH/2, 0),
                                                    FIELD_PENALTY_AREA_RADIUS * 0.98);
    Obstacle* myPenaltyArea_T = new Obstacle(Obstacle::eStatic, b2Vec2(z* FIELD_LENGTH/2, FIELD_PENALTY_AREA_WIDTH/2),
                                                    FIELD_PENALTY_AREA_RADIUS * 0.98);
    Obstacle* myPenaltyArea_D = new Obstacle(Obstacle::eStatic, b2Vec2(z* FIELD_LENGTH/2, -FIELD_PENALTY_AREA_WIDTH/2),
                                                    FIELD_PENALTY_AREA_RADIUS * 0.98);

    Obstacle* outFieldArea_R = new Obstacle(Obstacle::eStatic, b2Vec2(FIELD_LENGTH/2 + 300, 0),
                                                                    150*2 ,  FIELD_WIDTH, 0);
    Obstacle* outFieldArea_L = new Obstacle(Obstacle::eStatic, b2Vec2(-FIELD_LENGTH/2 - 300, 0),
                                                                    150*2 ,  FIELD_WIDTH, 0);

    myPenaltyArea_C->repulseStrenght = 1.5;
    myPenaltyArea_T->repulseStrenght = 1.5;
    myPenaltyArea_D->repulseStrenght = 1.5;

    penaltyAreaObstacles.push_back(myPenaltyArea_C);
    penaltyAreaObstacles.push_back(myPenaltyArea_T);
    penaltyAreaObstacles.push_back(myPenaltyArea_D);

    penaltyAreaObstacles.push_back(outFieldArea_L);
    penaltyAreaObstacles.push_back(outFieldArea_R);

    allRobotsObstacles.reserve(MAX_ID_NUM * 2);
    for(unsigned int i=0; i< MAX_ID_NUM *2; i++) {
        Obstacle* ob_ = new Obstacle(Obstacle::eRobot, b2Vec2(0, 0), ROBOT_RADIUS);
        ob_->repulseStrenght = 2.0;
        allRobotsObstacles.push_back(ob_);
    }

    ballObstacle = new Obstacle(Obstacle::eBall, b2Vec2(0,0), BALL_RADIUS);
}

Vector3D SSLSkill::Position()
{
    assert(owner_agent != 0);
    return owner_agent->robot->Position();
}

void SSLSkill::updateObstacles()
{
    SSLBall* actual_ball = world->mainBall();
    ballObstacle->m_transform.Set(b2Vec2(actual_ball->Position().X(),
                                         actual_ball->Position().Y()), 0);
}
