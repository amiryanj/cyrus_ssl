#include "sslskill.h"
#include "../ai/SSLWorldModel.h"
#include "../ai/SSLAnalyzer.h"
#include "../definition/SSLBall.h"
#include "../definition/SSLRobot.h"
#include "../transmitter/RobotCommandPacket.h"
#include "../transmitter/commandtransmitter.h"
#include "planner/planning/sslplanningagent.h"
#include "sslrole.h"
#include "sslagent.h"
#include "sslgamepositions.h"
#include "../paramater-manager/parametermanager.h"
#include "../debug-tools/logger.h"
#include "../debug-tools/networkplotter.h"

Vector3D SSLSkill::defaultTolerance;
Vector3D SSLSkill::accurateTolerance;

SSLSkill::SSLSkill(SSLAgent *parent)
{
    ParameterManager* pm = ParameterManager::getInstance();

    this->owner_agent = parent;
    defaultTolerance.setX(   pm->get<float>("skills.default_tolerance.x")    );
    defaultTolerance.setY(   pm->get<float>("skills.default_tolerance.y")    );
    defaultTolerance.setTeta(pm->get<float>("skills.default_tolerance.teta_deg")*M_PI/180.0);

    accurateTolerance.setX(   pm->get<float>("skills.accurate_tolerance.x")    );
    accurateTolerance.setY(   pm->get<float>("skills.accurate_tolerance.y")    );
    accurateTolerance.setTeta(pm->get<float>("skills.accurate_tolerance.teta_deg")*M_PI/180.0);

    rotate_call_deadline_time_ms = 0;
    avoid_rotate_deadline_time_ms = 0;

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
void SSLSkill::goToPoint(Vector3D target, const Vector3D &tolerance, MoveType move_type)
{
    this->kickTheBall = 0;
    target.setX(bound( target.X(),
                      -FIELD_LENGTH_2 + ROBOT_RADIUS,
                       FIELD_LENGTH_2 - ROBOT_RADIUS) );
    this->name = "Goto target";
    this->target = target;
    planner.deactivate();

    Vector3D diff = target - this->Position();
    if(       ( fabs(diff.X())    < tolerance.X() )
           && ( fabs(diff.Y())    < tolerance.Y() )
           && ( fabs(diff.Teta()) < tolerance.Teta() ) )
    {
        Vector3D zeroSpeed(0.0, 0.0, 0.0);
        controlSpeed(zeroSpeed, false);
    }
    else {
        goToSubGoal(target, tolerance, move_type);
    }
    NetworkPlotter::getInstance()->buildAndSendPacket("diff_to_target", diff.X());
}

void SSLSkill::goToPoint(Vector3D target, MoveType move_type)
{
    goToPoint(target, this->defaultTolerance, move_type);
}

void SSLSkill::goToPoint(Vector2D target, const Vector2D &tolerance, MoveType move_type)
{
    Vector3D target_with_set_orien(target, (target - Position().to2D()).arctan());
    goToPoint(target_with_set_orien, Vector3D(tolerance, defaultTolerance.Teta()), move_type);
}

void SSLSkill::goToPoint(Vector2D target, MoveType move_type)
{
    goToPoint(target, this->defaultTolerance.to2D(), move_type);
}

void SSLSkill::goGlobalSpeed(Vector3D &inp, bool use_controller)
{
    const float robot_linear_max_speed = owner_agent->robot->physic.max_lin_vel_mmps;
    float linear_vel_coeff = ParameterManager::getInstance()->get<double>("skills.linear_velocity_coeff");
    linear_vel_coeff = bound(linear_vel_coeff, 0.1, 1);
    float general_omega_coeff  = 0.7;
    float omega = 0.0f;

    Vector3D global_speed(inp.X() * linear_vel_coeff * robot_linear_max_speed,
                          inp.Y() * linear_vel_coeff * robot_linear_max_speed,
                          omega * general_omega_coeff);
    controlSpeed(global_speed, use_controller, true);
}

void SSLSkill::goLocalSpeed(Vector3D &inp, bool use_controller)
{
    const float robot_linear_max_speed = owner_agent->robot->physic.max_lin_vel_mmps;
    float linear_vel_coeff = ParameterManager::getInstance()->get<double>("skills.linear_velocity_coeff");
    linear_vel_coeff = bound(linear_vel_coeff, 0.1, 1);
    float general_omega_coeff  = 0.7;
    float omega = 0.0f;

    Vector3D local_speed(inp.X() * linear_vel_coeff * robot_linear_max_speed,
                          inp.Y() * linear_vel_coeff * robot_linear_max_speed,
                          omega * general_omega_coeff);
    controlSpeed(local_speed, use_controller , false);
}

void SSLSkill::goToSubGoal(const Vector3D &target, const Vector3D &tolerance, MoveType move_type)
{
    double large_radius = ParameterManager::getInstance()->get<double>("skills.large_radius_control");
    double small_raduis = ParameterManager::getInstance()->get<double>("skills.small_radius_control");
    Vector3D diff = target - this->Position();

    switch(move_type) {
    case eAccurateMove:
        accurateMove(this->Position(), target, accurateTolerance);
        break;

    case eSlowMove:
        slowMove(this->Position(), target, tolerance);
        break;

    case eFastMove:
        fastMove(this->Position(), target, tolerance);
        break;

    case eAutoMove:
        if(diff.lenght2D() > large_radius)
        {
            fastMove(this->Position(), target, tolerance);
        }
        else if(diff.lenght2D() > small_raduis)
        {
            slowMove(this->Position(), target, tolerance);
        }
        else {
            accurateMove(this->Position(), target, accurateTolerance);
        }
        break;
    }

}

void SSLSkill::goToPointWithPlanner(const Vector3D &target,
                                    const Vector3D &tolerance,
                                    bool considerPenaltyArea,
                                    float ball_obs_radius,
                                    float robot_obs_radius,
                                    MoveType move_type)
{
    this->name = "Plan and go to point";
    this->target = target;
    this->kickTheBall = false;

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
            ob_->setRadius(robot_obs_radius);
            ob_->transform.Set(Vector2D(rob_->Position().X(), rob_->Position().Y()).toB2vec2(),
                               rob_->Position().Teta());
            allObstacles.push_back(ob_);
        }
    }

    if(ball_obs_radius != 0) {
        ballObstacle->setRadius(ball_obs_radius);
        allObstacles.push_back(ballObstacle);
    }

    planner.setStaticObstacles(allObstacles);

    // we dont need to run all planners in every frame
    if( (SSLGame::getInstance()->game_running_counter % MAX_ID_NUM) == owner_agent->getID())
        planner.solve();

    int plan_lenght = planner.getTrajectory().length();
    if(owner_agent->getID() == 1 )
    {
        this->avoid_rotate_deadline_time_ms = 0;
    }
    if( plan_lenght >1 )   {
        Station subGoal = planner.getTrajectory().getStation(1);
        if(plan_lenght > 2)   {
            Vector3D tolerance_without_orien = tolerance;
            tolerance_without_orien.setTeta(M_PI_2);
            this->goToSubGoal(subGoal.getPosition(), tolerance_without_orien, eFastMove);
        }   else   {
            this->goToSubGoal(subGoal.getPosition(), tolerance, move_type);
        }
    }
}

// this function is responsible for approaching the ball
// and setting the orientation such that it can kick the ball
// it should get the target to shoot
void SSLSkill::goAndKick(const Vector2D kick_point,const  Vector2D kick_target, float kickStrenghtNormal)
{
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
              && (dist_robot_and_ball_line > (ROBOT_RADIUS + BALL_RADIUS) * .5) );

    }

    if((this->Position().to2D() - kick_point).lenght() > 500 || !is_robot_behind_ball)  {
        this->kickTheBall = 0;
        Vector3D behind_ball_target = SSL::Position::KickStylePosition(kick_point, kick_target, 100);
        Vector3D tolerance(ROBOT_RADIUS/2, ROBOT_RADIUS/2, M_PI/4.0);
        goToPointWithPlanner(behind_ball_target, tolerance, false, 0.7 * BALL_RADIUS, 0, eFastMove);
    }

    else {
        planner.deactivate();
        this->name = "Kick ball";
        Vector2D diff_between_ball_and_target = (kick_point - kick_target);
        LineSegment behind_ball_line(kick_point,
                                     kick_point + diff_between_ball_and_target.normalized() * 1000);
        float teta_diff = continuousRadian((-diff_between_ball_and_target).arctan() - this->Position().Teta(),
                                           -M_PI);



        if(this->Position().to2D().distToLine(behind_ball_line) > 40.0)  {
            target = Vector3D(behind_ball_line.nearestPointFrom(this->Position().to2D()), 0);
            Vector3D diff_to_target = target - this->Position();
            controlSpeed(Vector3D(diff_to_target.to2D().normalized() * 0.2 * 3000, 0.0),
                         kickTheBall);
        }  else if(fabs(teta_diff) > M_PI / 10.0) {
                rotate(0.12 * sgn(teta_diff));
        }
        else {
            this->kickTheBall = true;
            Vector3D forward_speed(.2, 0, 0);
            forward_speed.rotate(this->Position().Teta());
            controlSpeed(forward_speed * 3000, true);
        }


    }



//    if( this->Position().to2D().distToLine(behind_ball_line) < 20 &&
//            this->Position().to2D() - kick_point)  {
//        if( fabs(this->Position().Teta() - atan(behind_ball_line.slope())) < M_PI/9.0 ) {

//        }
//    }

//    if(analyzer->canKick(owner_agent->robot))  {
//    }
//    else if(is_robot_behind_ball && (diff_between_ball_and_target.lenght() < 500))  {
//        planner.deactive();
//        Vector3D kick_ball_point = SSL::Position::KickStylePosition(kick_point, kick_target, -50);
//        target = kick_ball_point;

//        LineSegment l((kick_point - kick_ball_point.to2D()).normalized() * 1000, kick_point);
//        float dist_to_line = this->Position().to2D().distToLine(l);
//        if(fabs(dist_to_line) > 40) {
//            target = Vector3D(kick_point + (kick_point - kick_target).normalized() * 40, target.Teta());
//            Vector3D tolerance(20, 20, M_PI/6.0);
//            this->kickTheBall = 1;
//            goToSubGoal(target, tolerance, eAccurateMove);
//        }
//        else if(fabs((target - this->Position()).Teta()) > M_PI/8.0)
//        {
//            this->kickTheBall = 1;
//            rotate( sgn((target - Position()).Teta()) * 0.14);
//        }
//        else {
//            this->kickTheBall = 1;
//            Vector3D tolerance(20, 20, M_PI/9.0);
//            goToSubGoal(target, tolerance, eAutoMove);
//        }
//    }
//    else {
//        this->kickTheBall = 0;
//        Vector3D behind_ball_target = SSL::Position::KickStylePosition(kick_point, kick_target, 100);
//        Vector3D tolerance(ROBOT_RADIUS/2, ROBOT_RADIUS/2, M_PI/4.0);
//        goToPointWithPlanner(behind_ball_target, tolerance, false, 0.7 * BALL_RADIUS, 0);
//    }
}

void SSLSkill::goAndChip(double chipStrenghtNormal)
{
    this->name = "Chip ball";
    planner.deactivate();
}

void SSLSkill::goBehindBall(Vector2D ball_position)
{
    assert(0);
}

double SSLSkill::computeVelocityStrenghtbyDistance(double dist , double max_speed)
{
    double stop_radius_A = 400 /*mili meter*/ ; // max_speed / 1.5;
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

    ratio = bound(ratio , 0.14 , 1.0);
    return ratio;
}
void SSLSkill::fastMove(const Vector3D &current_pos,
                    const Vector3D &target_pos,
                    const Vector3D &tolerance )
{
    Vector3D diff = target_pos - current_pos;
    diff.setTeta(continuousRadian(diff.Teta(), -M_PI));

    float linear_vel_coeff = ParameterManager::getInstance()->get<double>("skills.linear_velocity_coeff");
    linear_vel_coeff = bound(linear_vel_coeff, 0.1, 1);

    float omega = 0;
    float general_omega_coeff  = 0.7;
    if(diff.lenght2D() < 150) {
        linear_vel_coeff = 1.2 * computeVelocityStrenghtbyDistance(diff.lenght2D(),
                                                        owner_agent->robot->physic.max_lin_vel_mmps);
        if ( fabs(diff.Teta()) > (2.0/3.0)*M_PI )  {
            omega = 0.32 * sgn(diff.Teta());
            linear_vel_coeff *= 0.65;
        }
        else if ( fabs(diff.Teta()) > (1.0/5.0)*M_PI ) {
            omega = 0.15 * sgn(diff.Teta());
            linear_vel_coeff *= 0.75;
        }
        else if ( fabs(diff.Teta()) > tolerance.Teta()) {
            omega = 0.12 * sgn(diff.Teta());
            linear_vel_coeff *= 0.85;
        }
        else {
            omega = 0;
        }

        if(diff.lenght2D() < tolerance.lenght2D())
            if(fabs(diff.Teta()) < tolerance.Teta()) {
                rotate(0.13 * sgn(diff.Teta()));
                return;
            }
    }

    // set omega in different orientations    

    const float robot_linear_max_speed = owner_agent->robot->physic.max_lin_vel_mmps;

    diff.normalize2D();
    Vector3D desired_gloabal_speed(diff.to2D().normalized().X() * linear_vel_coeff * robot_linear_max_speed,
                                   diff.to2D().normalized().Y() * linear_vel_coeff * robot_linear_max_speed,
                                   omega    * general_omega_coeff);

    controlSpeed(desired_gloabal_speed, true /*use controller*/);
}

void SSLSkill::slowMove(const Vector3D &current_pos, const Vector3D &target_pos, const Vector3D &tolerance, double speed_coeff)
{
    Vector3D diff = target_pos - current_pos;
    diff.setTeta(continuousRadian(diff.Teta(), -M_PI));

    double linear_vel_strenght;
    if(speed_coeff > 0)
        linear_vel_strenght = speed_coeff;
    else {
        linear_vel_strenght = 1.4 * computeVelocityStrenghtbyDistance(diff.lenght2D(),
                                                        owner_agent->robot->physic.max_lin_vel_mmps);
    }

    // set omega in different orientations
    float omega = 0;
    if ( fabs(diff.Teta()) > (2.0/3.0)*M_PI )  {
        omega = 0.25 * sgn(diff.Teta());
        linear_vel_strenght = std::min(0.45, linear_vel_strenght);
    }
    else if ( fabs(diff.Teta()) > (1.0/5.0)*M_PI ) {
        omega = 0.18 * sgn(diff.Teta());
        linear_vel_strenght = std::min(0.6, linear_vel_strenght);
    }
    else if ( fabs(diff.Teta()) > tolerance.Teta()) {
        omega = 0.12 * sgn(diff.Teta());
        linear_vel_strenght = std::min(0.85, linear_vel_strenght);
    }
    else {
        omega = 0;
    }
//    omega = 0;


    float general_linear_coeff = 0.8;
    float general_omega_coeff  = 0.4;

    linear_vel_strenght *= general_linear_coeff;
//    if(this->owner_agent->getID() == 3) {
//        NetworkPlotter::getInstance()->buildAndSendPacket("omega", omega);
//        NetworkPlotter::getInstance()->buildAndSendPacket("vel_strenght", linear_vel_strenght);
//    }

    const float robot_linear_max_speed = owner_agent->robot->physic.max_lin_vel_mmps;

    diff.normalize2D();
    Vector3D desired_gloabal_speed(diff.to2D().normalized().X() * linear_vel_strenght * robot_linear_max_speed,
                                   diff.to2D().normalized().Y() * linear_vel_strenght * robot_linear_max_speed,
                                   omega    * general_omega_coeff);

    controlSpeed(desired_gloabal_speed, true /*use controller*/);

}

void SSLSkill::accurateMove(const Vector3D &current_pos, const Vector3D &target_pos, const Vector3D &tolerance)
{
    Vector3D diff = target_pos - current_pos;
    diff.setTeta(continuousRadian(diff.Teta(), -M_PI));


    // set omega in different orientations

    double omega = 0.15 * sgn(diff.Teta());
    double current_time = currentTimeMSec();
    printf("Current Time: %.9f \n", current_time);
//    cout << "current_time: "<< current_time << endl;
    for(int i=0;i<1;i++) {
        if(current_time < rotate_call_deadline_time_ms)
        {
            rotate(omega);
            return;
        }
        else if(current_time < avoid_rotate_deadline_time_ms)
        {
            break;
        } else {
            if(fabs(diff.Teta()) > tolerance.Teta()) {
                double diff_teta = diff.Teta();
                const double omega_to_time_coeff = 1000.0;
                double rotation_time = fabs(diff_teta * omega * omega_to_time_coeff);
                printf("Rotation Time: %.56f \n \n", rotation_time);
                rotate_call_deadline_time_ms = current_time + rotation_time;
                avoid_rotate_deadline_time_ms = rotate_call_deadline_time_ms + 1500 /*mili sec*/;
            }
            else {
                break;
            }
        }
    }

    double linear_vel_strenght = 0.25;

    const float robot_linear_max_speed = owner_agent->robot->physic.max_lin_vel_mmps;

    diff.normalize2D();
    Vector3D desired_global_speed(diff.to2D().normalized().X() * linear_vel_strenght * robot_linear_max_speed,
                                   diff.to2D().normalized().Y() * linear_vel_strenght * robot_linear_max_speed,
                                   0  );

    controlSpeed(desired_global_speed, true /*use controller*/);
}

//void SSLSkill::rotateByDegree(float current_orien_deg, float rotation_deg, float omega)
//{
//    rotate(rotation_deg * (M_PI/180.0), omega);
//}

void SSLSkill::rotate(float omega)
{
//    orientation_counter ++;
//    current_orien += orientation_counter * (M_PI/20);


    this->name = "Rotate";
    {
        Vector3D rotate_speed(0, 0, omega);
        controlSpeed(rotate_speed, true);
    }
}


void SSLSkill::controlSpeed(const Vector3D& desired_speed, bool use_controller, bool global_vel)
{
    Vector3D actual_local_speed = this->owner_agent->robot->localSpeed();
    Vector3D desired_local_speed = desired_speed;
    this->desiredGlobalSpeed = desired_speed;
    if(global_vel) {
        desired_local_speed.rotate(-1 * Position().Teta());
    }
    else {
        desiredGlobalSpeed.rotate(Position().Teta());
    }

    Vector3D applied_local_speed;
    if(use_controller) {
        controller.setPoint(desired_local_speed, actual_local_speed);
        applied_local_speed = controller.getControl();
    }
    else {
        float max_speed = owner_agent->robot->physic.max_lin_vel_mmps;
        applied_local_speed = desired_local_speed;
        applied_local_speed.setX(applied_local_speed.X() / max_speed);
        applied_local_speed.setY(applied_local_speed.Y() / max_speed);
    }

    CommandTransmitter::getInstance()->buildAndSendPacket(owner_agent->getID(),
                                                          applied_local_speed,
                                                          this->kickTheBall);

    if(owner_agent->getID() == ParameterManager::getInstance()->get<int>("skills.under_test_robot"))
    {
//        NetworkPlotter::getInstance()->buildAndSendPacket("applied_strenght", desiredGlobalSpeed.Teta()*1000.0);
//        NetworkPlotter::getInstance()->buildAndSendPacket("Omega", desiredGlobalSpeed.Teta() * 100.0);

        vector<double> speed_to_sent;
        vector<string> speed_labels;
        speed_to_sent.push_back(desired_local_speed.X() + 0.1);
        speed_labels.push_back("desire_");
        speed_to_sent.push_back(actual_local_speed.X() + 0.1);
        speed_labels.push_back("actual_");
        speed_to_sent.push_back(applied_local_speed.X() * 3000 + 0.1);
        speed_labels.push_back("applied_");
        speed_to_sent.push_back(1000);
        speed_labels.push_back("1000");
        NetworkPlotter::getInstance()->buildAndSendPacket("control_x", speed_to_sent, speed_labels);
    }
}

void SSLSkill::initializePlanner()
{
    RectangularFieldBound *bound = new RectangularFieldBound(-1.1 * FIELD_LENGTH_2,
                                              1.1 * FIELD_LENGTH_2,
                                             -1.1 * FIELD_WIDTH_2,
                                              1.1 * FIELD_WIDTH_2 );
    planner.setBound(bound);

    SSLPlanningAgent *planning_agent = new SSLPlanningAgent;
    planning_agent->mass = 3.0; // kilo gram
    planner.setPlanningAgent(planning_agent);

    // initializing field obstacles for agent
    // ****************************************************************************************
    penaltyAreaObstacles.reserve(5);
    int z = ParameterManager::getInstance()->get<int>("general.game.our_side");
    Obstacle* myPenaltyArea_C = new Obstacle(Vector2D(z* FIELD_LENGTH_2, 0),
                                             FIELD_PENALTY_AREA_RADIUS * 0.98, "our penalty - center");
    Obstacle* myPenaltyArea_T = new Obstacle(Vector2D(z* FIELD_LENGTH_2, FIELD_PENALTY_AREA_WIDTH_2),
                                             FIELD_PENALTY_AREA_RADIUS * 0.98, "our penalty - top");
    Obstacle* myPenaltyArea_D = new Obstacle(Vector2D(z* FIELD_LENGTH_2, -FIELD_PENALTY_AREA_WIDTH_2),
                                             FIELD_PENALTY_AREA_RADIUS * 0.98, "our penalty - down");

    Obstacle* outFieldArea_R = new Obstacle(Vector2D(FIELD_LENGTH_2 + 300, 0),
                                            150 * 2 ,  FIELD_WIDTH, 0.0f, "right out");
    Obstacle* outFieldArea_L = new Obstacle(Vector2D(-FIELD_LENGTH_2 - 300, 0),
                                            150 * 2 ,  FIELD_WIDTH, 0.0f, "left out");

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
        // TODO: set the id and color of the robot in obstacle detail field, will be useful
        Obstacle* ob_ = new Obstacle(Vector2D(0, 0), ROBOT_RADIUS, "robot");
        ob_->repulseStrenght = 2.0;
        allRobotsObstacles.push_back(ob_);
    }

    ballObstacle = new Obstacle(Vector2D(0, 0), BALL_RADIUS, "ball");
}

Vector3D SSLSkill::Position()
{
    assert(owner_agent != 0);
    return owner_agent->robot->Position();
}

void SSLSkill::updateObstacles()
{
    SSLBall* actual_ball = world->mainBall();
    ballObstacle->transform.Set(b2Vec2(actual_ball->Position().X(),
                                         actual_ball->Position().Y()), 0);
}
