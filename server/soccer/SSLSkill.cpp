#include "SSLSkill.h"
#include "../definition/sslagent.h"
#include "../ai/SSLWorldModel.h"
#include "../ai/SSLAnalyzer.h"
#include "../definition/SSLBall.h"
#include "../definition/SSLRobot.h"
#include "../transmitter/RobotCommandPacket.h"
#include "../transmitter/commandtransmitter.h"
#include "roles/sslrole.h"
#include "sslgamepositions.h"

void SSLSkill::halt(SSLAgent *agent)
{
    assert(agent != NULL);

    agent->skill_in_use = "Halt";
    agent->planner.deactive();

    Vector3D zeroSpeed(0, 0, 0);
    controlSpeed(agent, zeroSpeed, false);
}

void SSLSkill::goToPoint(SSLAgent *agent, Vector3D target, const Vector3D &tolerance)
{
    agent->skill_in_use = "Go to point";
    agent->planner.deactive();

    agent->tempTarget = target;
    target.setTeta(SSL::continuousRadian(target.Teta(), agent->robot->Position().Teta() - M_PI));

    Vector3D diff = target - agent->robot->Position();
    if((fabs(diff.X()) < tolerance.X())
           && (fabs(diff.Y()) < tolerance.Y())
           && (fabs(diff.Teta()) < tolerance.Teta()))
    {
        Vector3D zeroSpeed;
        zeroSpeed.setZero();
        controlSpeed(agent, zeroSpeed, false);
    }
    else {
        Vector3D speed = calcSpeed(agent->robot->Position(), target);
        controlSpeed(agent, speed, true);
    }
}

void SSLSkill::goToPointWithPlanner(SSLAgent* agent, const Vector3D &target, const Vector3D &tolerance,
                                    bool considerPenaltyArea, float ball_obs_radius, float robot_obs_radius)
{
    cout << "Agent Number [" << agent->getID() << "] => Go to point with planner" << endl;

    agent->skill_in_use = "Plan and go to point";

    Station init_state;
    init_state.setPosition(agent->robot->Position());
    init_state.setVelocity(agent->robot->Speed());
    agent->planner.setInitialState(init_state);

    GoalState goal;
    goal.goal_point.setPosition(target);
    goal.tolerance.setPosition(tolerance);
    agent->planner.setGoalRegion(goal);

    agent->tempTarget = target;

    ObstacleSet allObstacles;
    allObstacles.reserve(2*MAX_ID_NUM + 6);

    if(considerPenaltyArea)    {// for all robots except goal keeper
        // insert all static obstacles related to penalty area
        allObstacles.insert(allObstacles.begin(),
                            game->penaltyAreaObstacles.begin(), game->penaltyAreaObstacles.end());
    }

    // update position of obstacles
    if(robot_obs_radius != 0) {
        vector<SSLRobot* > all_actual_robots = SSLWorldModel::getInstance()->getInFieldRobotsExcept(agent->robot);
        for(uint i =0; i<all_actual_robots.size(); i++)
        {
            SSLRobot* rob_ = all_actual_robots[i];
            Obstacle* ob_  = game->allRobotsObstacles[i];
            ob_->shape->m_radius = robot_obs_radius;
            ob_->m_transform.Set(Vector2D(rob_->Position().X(), rob_->Position().Y()).toB2vec2(), rob_->Position().Teta());
            allObstacles.push_back(ob_);
        }
    }

    if(ball_obs_radius != 0) {
        game->ballObstacle->shape->m_radius = ball_obs_radius;
        allObstacles.push_back(game->ballObstacle);
    }

    agent->planner.setStaticObstacles(allObstacles);

    agent->planner.solve();
//        assert(planner.planningResult == true); // this assumption is not true

//    if(agent->planner.planningResult)
    {
        Vector3D vel = agent->planner.getControl();
        vel.normalize2D();

        Vector3D diff = target - agent->robot->Position();
        float speedCoefficient = 1;
//        if(diff.lenght2D() < 600) // milli meter
//            speedCoefficient = (diff.lenght2D() / 600.0 );


        if(diff.lenght2D() > 1700.0) {
            speedCoefficient = 1.7;
        }

        if(diff.lenght2D() < 800.0) {
            if(diff.lenght2D() > 250.0) {// milli meter
                speedCoefficient = diff.lenght2D() / 1000.0;
            }
            else {
                speedCoefficient = 200.0/1000.0;
            }
        }

        Vector3D desiredSpeed = vel * speedCoefficient;
        controlSpeed(agent, desiredSpeed, true);
    }
//    else {
//        Vector3D zeroSpeed;
//        zeroSpeed.setZero();
//        controlSpeed(agent, zeroSpeed, true);
//    }
}


// this function is responsible for approaching the ball
// and setting the orientation such that it can kick the ball
// it should get the target to shoot
void SSLSkill::goAndKick(SSLAgent *agent, Vector2D kick_target, double kickStrenghtNormal)
{
    agent->skill_in_use = "Kick ball";
    agent->planner.deactive();
    Vector2D catch_point = analyzer->whenWhereCanRobotCatchTheBall(agent->robot).m_position;
    Vector3D target = SSL::Position::KickStylePosition(catch_point, kick_target, -40);
//    Vector3D target = KickStylePosition(SSLWorldModel::getInstance()->mainBall()->Position(), kick_target, -40);
    agent->tempTarget = target;

    float diff_teta = target.Teta() - agent->robot->Position().Teta();
    diff_teta = continuousRadian(diff_teta, -M_PI);

    if( diff_teta > (M_PI / 6.0) ) {
        agent->skill_in_use = "Rotate";
        Vector3D speed(0.0, 0.0, diff_teta /2.0);
        controlSpeed(agent, speed, false);
    }

    else if(analyzer->canKick(agent->robot)) {
        Vector3D speed(.3, 0, 0); // go fast forward
        CommandTransmitter::getInstance()->buildAndSendPacket(agent->getID(), speed, kickStrenghtNormal);
        //        controlSpeed(agent, speed, true);
        // TODO send kick packet
    }

    else {
        Vector3D speed = calcSpeed(agent->robot->Position(), target);
        speed *= 1.2;
        controlSpeed(agent, speed, true);
    }
}

void SSLSkill::goAndChip(SSLAgent *agent, double chipStrenghtNormal)
{
    agent->skill_in_use = "Chip ball";
    agent->planner.deactive();
}

Vector3D SSLSkill::calcSpeed(const Vector3D &current, const Vector3D &target)
{
    Vector3D diff = target - current;
    float Coeffs[3] = {1, 1, 1};
    if( diff.lenght2D() < 800 )  {
        if(diff.lenght2D() > 300.0) {// milli meter
            Coeffs[0] = diff.lenght2D() / 1000.0;
            Coeffs[1] = 1.1 * diff.lenght2D() / 1000.0;
        }
        else if (diff.lenght2D() > 100.0){
            Coeffs[0] = 300.0 / 1000.0;
            Coeffs[1] = 350.0 / 1000.0;
        }
        else {
            Coeffs[0] = 150.0 / 1000.0;
            Coeffs[1] = 180.0 / 1000.0;
        }
    }

    Coeffs[2] = 0.1;

    diff.normalize2D();

    Vector3D speed(diff.X() * Coeffs[0], diff.Y() * Coeffs[1], diff.Teta() * Coeffs[2]);
    cout << speed.X() << " " << speed.Y() << " " << speed.Teta() << endl;
    return speed;
}

void SSLSkill::controlSpeed(SSLAgent *agent, const Vector3D& speed, bool use_controller)
{
    float speedDiscountRate = 0.55;

    agent->desiredGlobalSpeed = speed * speedDiscountRate;

    float angularSpeedCoefficient = 0.15;
    if(agent->role->m_type == SSLRole::e_GoalKeeper )   {
        angularSpeedCoefficient = 0.05;
    }

    // because controller is not working yet
    if(use_controller) {
        agent->controller.setPoint(agent->desiredGlobalSpeed, agent->robot->Speed()/400);
        agent->appliedGlobalSpeed = agent->controller.getControl();
    }
    else {
        agent->appliedGlobalSpeed = agent->desiredGlobalSpeed;
    }

    agent->appliedGlobalSpeed.setTeta(agent->appliedGlobalSpeed.Teta() * angularSpeedCoefficient);

    agent->appliedLocalSpeed = agent->appliedGlobalSpeed;
    agent->appliedLocalSpeed.rotate( -1 * agent->robot->orien());

    CommandTransmitter::getInstance()->buildAndSendPacket(agent->getID(), agent->appliedLocalSpeed);
}

