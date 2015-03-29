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

SSLSkill::SSLSkill(SSLAgent *parent)
{
    ParameterManager* pm = ParameterManager::getInstance();

    this->owner_agent = parent;
    defaultTolerance.setX(   pm->get<float>("skill.default_tolerance.x")    );
    defaultTolerance.setY(   pm->get<float>("skill.default_tolerance.x")    );
    defaultTolerance.setTeta(pm->get<float>("skill.default_tolerance.teta_deg")*M_PI/180.0);

  // initialize planner
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
    int z = pm->get<int>("game.our_color");
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
    this->name = "Go to target";
    this->target = target;
    planner.deactive();

    Vector3D diff = target - this->Position();
    if(       ( fabs(diff.X()) < tolerance.X() )
           && ( fabs(diff.Y()) < tolerance.Y() )
           && ( fabs(diff.Teta()) < tolerance.Teta() ) )
    {
        Vector3D zeroSpeed (0.0, 0.0, 0.0);
        controlSpeed(zeroSpeed, false);
    }
    else {
        move(this->Position(), target, tolerance);
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

    planner.solve();
//    Station subGoal = planner.getFirstSubGoal();
    int plan_lenght = planner.getTrajectory().length();
    if( plan_lenght >1 )   {
        Station subGoal = planner.getTrajectory().getStation(1);
        if(plan_lenght > 2)   {
            this->goToPoint(subGoal.getPosition().to2D(), tolerance.to2D());
        }   else   {
            this->goToPoint(subGoal.getPosition(), tolerance);
        }
    }


}

// this function is responsible for approaching the ball
// and setting the orientation such that it can kick the ball
// it should get the target to shoot
void SSLSkill::goAndKick(Vector2D kick_target, double kickStrenghtNormal)
{
    this->name = "Kick ball";
    planner.deactive();

    Vector2D catch_point = analyzer->whenWhereCanRobotCatchTheBall(owner_agent->robot).m_position;
    target = SSL::Position::KickStylePosition(catch_point, kick_target, -40);

    if(analyzer->canKick(owner_agent->robot))  {
        Vector3D speed(0.1, 0, 0); // go fast in forward direction to reach ball and then kick it
        CommandTransmitter::getInstance()->buildAndSendPacket(owner_agent->getID(), speed, kickStrenghtNormal);
    }   else   {
        goToPointWithPlanner(target, defaultTolerance, false, 2*BALL_RADIUS, 0);
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

void SSLSkill::move(const Vector3D &current_pos, const Vector3D &target_pos, const Vector3D &tolerance)
{
    Vector3D diff = target_pos - current_pos;
    diff.setTeta(continuousRadian(diff.Teta(), -M_PI));

    float omega = 0;
    float linear_vel_strenght = 1.0;
    if ( abs(diff.Teta()) > M_PI_2 )  {
        omega = 0.5 * sgn(diff.Teta());
        linear_vel_strenght = 0.2;
    }
    else if ( diff.Teta() > M_PI_4 ) {
        omega = 0.2 * sgn(diff.Teta());
        linear_vel_strenght = 0.4;
    }
    else if (abs(diff.Teta() > tolerance.Teta())) {
        omega = 0.2 * sgn(diff.Teta());
        linear_vel_strenght = 0.6;
    }
    else {
        omega = 0;
        linear_vel_strenght = 1;
    }

    float Coeffs[3] = {1, 1, 1};
    if( diff.lenght2D() < 800 )  {
        if(diff.lenght2D() > 300.0)  {   // milli meter
            Coeffs[0] = diff.lenght2D() / 1000.0;
            Coeffs[1] = 1.1 * diff.lenght2D() / 1000.0;
        }  else if (diff.lenght2D() > 100.0)   {
            Coeffs[0] = 300.0 / 1000.0;
            Coeffs[1] = 350.0 / 1000.0;
        }
        else  {
            Coeffs[0] = 150.0 / 1000.0;
            Coeffs[1] = 180.0 / 1000.0;
        }
    }

    Coeffs[2] = 0.1;

    diff.normalize2D();

    Vector3D speed(diff.X() * Coeffs[0] * linear_vel_strenght,
                   diff.Y() * Coeffs[1] * linear_vel_strenght,
                   omega);
    controlSpeed(speed, true);
}

void SSLSkill::controlSpeed(const Vector3D& speed, bool use_controller)
{
    this->desiredGlobalSpeed = speed;
    // because controller is not working yet
//    if(use_controller) {
//        controller.setPoint(agent->desiredGlobalSpeed, agent->robot->Speed()/400);
//        appliedGlobalSpeed = controller.getControl();
//    }
//    else {
    this->appliedGlobalSpeed = desiredGlobalSpeed;
//    }

    Vector3D appliedLocalSpeed = appliedGlobalSpeed;
    appliedLocalSpeed.rotate( -1 * Position().Teta());

    CommandTransmitter::getInstance()->buildAndSendPacket(owner_agent->getID(), appliedLocalSpeed);
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
