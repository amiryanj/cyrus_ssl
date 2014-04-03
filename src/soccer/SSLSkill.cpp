#include "SSLSkill.h"
#include "../definition/sslagent.h"
#include "../ai/SSLWorldModel.h"
#include "../ai/SSLAnalyzer.h"
#include "../definition/SSLBall.h"
#include "../transmitter/RobotCommandPacket.h"
#include "../transmitter/commandtransmitter.h"

void SSLSkill::halt(SSLAgent *agent)
{
    assert(agent != NULL);

    agent->skill_in_use = "Halt";
    agent->planner.deactive();

    Vector3D zeroSpeed;
    zeroSpeed.setZero();

    controlSpeed(agent, zeroSpeed);
}

void SSLSkill::goToPoint(SSLAgent *agent, Vector3D target, Vector3D tolerance)
{
    cout << "Agent Number [" << agent->getID() << "] => Go to point " << endl;

    agent->skill_in_use = "Go to point";
    agent->planner.deactive();

    agent->tempTarget = target;

    Vector3D diff = target - agent->robot->Position();
    if((fabs(diff.X()) < tolerance.X())
           && (fabs(diff.Y()) < tolerance.Y())
           && (fabs(diff.Teta()) < tolerance.Teta()))
    {
        Vector3D zeroSpeed;
        zeroSpeed.setZero();
        controlSpeed(agent, zeroSpeed);
    }
    else {
        float speedCoefficient = 1;
        if(diff.lenght2D() < 400) // milli meter
            speedCoefficient = (diff.lenght2D() / 400.0);

        diff.normalize2D();
        Vector3D desiredSpeed = diff * speedCoefficient;
        controlSpeed(agent, desiredSpeed);
    }
}

void SSLSkill::goToPointWithPlanner(SSLAgent* agent, Vector3D target, Vector3D tolerance,
                                    bool considerPenaltyArea, float ball_ob_radius, float robot_ob_radius)
{
    cout << "Agent Number [" << agent->getID() << "] => Go to point with planner" << endl;

    agent->skill_in_use = "Plan and go to point";
    Station init_state;
    init_state.setPosition(agent->robot->Position());
    init_state.setVelocity(agent->robot->Speed());

    agent->planner.setInitialState(init_state);
    GoalState goal;
    goal.goal_point.position = target;
    goal.tolerance.position = tolerance;
    agent->planner.setGoalRegion(goal);

    agent->tempTarget = target;

    ObstacleSet tmpAllObstacles;
    tmpAllObstacles.reserve(2*MAX_ID_NUM + 6);

    if(considerPenaltyArea)
        tmpAllObstacles.insert(tmpAllObstacles.begin(), game->penaltyAreaObs.begin(), game->penaltyAreaObs.end());

    // update position of obstacles
    if(robot_ob_radius != 0) {
        vector<SSLRobot* > all_actual_robots = SSLWorldModel::getInstance()->all_inFieldsExcept(agent->robot);
        for(uint i =0; i<all_actual_robots.size(); i++)
        {
            SSLRobot* rob_ = all_actual_robots[i];
            Obstacle* ob_  = game->allRobotsObs[i];
            ob_->shape->m_radius = robot_ob_radius;
            ob_->m_transform.Set(Vector2D(rob_->Position().X(), rob_->Position().Y()).b2vec2(), rob_->Position().Teta());
            tmpAllObstacles.push_back(ob_);
        }
    }

    if(ball_ob_radius != 0) {
        game->ballOb->shape->m_radius = ball_ob_radius;
        tmpAllObstacles.push_back(game->ballOb);
    }

    agent->planner.setStaticObstacles(tmpAllObstacles);

    agent->planner.solve();
//        assert(planner.planningResult == true); // this assumption is not true

    if(agent->planner.planningResult) {
        Vector3D vel = agent->planner.getControl();
        vel.normalize2D();

        Vector3D diff = target - agent->robot->Position();
        float speedCoefficient = 1;
        if(diff.lenght2D() < 400) // milli meter
            speedCoefficient = (diff.lenght2D() / 400.0 );

        Vector3D desiredSpeed = vel * speedCoefficient;
        controlSpeed(agent, desiredSpeed);
    }
    else {
        Vector3D zeroSpeed;
        zeroSpeed.setZero();
        controlSpeed(agent, zeroSpeed);
    }
}


// this function is responsible for approaching the ball
// and setting the orientation such that it can kick the ball
// TO DO:
// it should get the target to shoot
void SSLSkill::goAndKick(SSLAgent *agent, double kickStrenghtNormal)
{
    agent->skill_in_use = "Kick ball";
    Vector3D target = KickStylePosition(SSLWorldModel::getInstance()->mainBall()->Position(), opponentGoalCenter());
    agent->tempTarget = target;
    agent->planner.deactive();
    if(analyzer->canKick(agent->robot)) {
        Vector3D speed(1, 0, 0); // go fast forward
        buildAndSendPacket(agent->getID(), speed, kickStrenghtNormal);
    }
    else {
        Vector3D diff = target - agent->robot->Position();
        diff.normalize2D();
        controlSpeed(agent, diff);
    }
}

void SSLSkill::goAndChip(SSLAgent *agent, double chipStrenghtNormal)
{
    agent->skill_in_use = "Chip ball";
    agent->planner.deactive();
}

void SSLSkill::buildAndSendPacket(int id, Vector3D &vel, float kickPower)
{
    bool useNewRobotWheelAngles = true;

    RobotCommandPacket pkt(vel, useNewRobotWheelAngles, kickPower);

    CommandTransmitter::getInstance()->send(id, pkt);
}

void SSLSkill::printRobotAppliedSpeed(SSLAgent *agent, ostream &stream)
{
    stream  << "Applied Speed for robot #" << agent->getID()
            << " is: Vx= " << agent->appliedLocalSpeed.X()
            << " Vy= "     << agent->appliedLocalSpeed.Y()
            << " ,V <angle>= " << agent->appliedLocalSpeed.to2D().arctan()
            << " <speed>= "<< agent->appliedLocalSpeed.lenght2D()
            << " omega= "  << agent->appliedLocalSpeed.Teta() << endl;
}

Vector2D SSLSkill::opponentPenaltyPoint()
{
    return Vector2D(game->opponentSide() * (FIELD_LENGTH/2 - FIELD_PENALTY_DISTANCE), 0);
}

Vector2D SSLSkill::opponentGoalCenter()
{
    return Vector2D(game->opponentSide() * (FIELD_LENGTH/2), 0);
}

Vector2D SSLSkill::ourGoalCenter()
{
    return Vector2D(game->ourSide() * (FIELD_LENGTH/2), 0);
}

Vector3D SSLSkill::KickStylePosition(Vector2D point, Vector2D target)
{
    Vector2D dir = (target - point).normalized();
    float orien = dir.arctan();
    Vector3D pos(point - dir * (BALL_RADIUS + ROBOT_RADIUS + 100), orien);
    return pos;
}

void SSLSkill::controlSpeed(SSLAgent *agent, const Vector3D& speed)
{
    float speedDiscountRate = .4;
    agent->desiredGlobalSpeed = speed * speedDiscountRate;

    float angularSpeedCoefficient = 0.0;

    // because controller is not working yet
    agent->controller.setPoint(agent->desiredGlobalSpeed, agent->robot->Speed()/2000);
    agent->appliedGlobalSpeed = agent->controller.getControl();

    agent->appliedGlobalSpeed.setTeta(agent->appliedGlobalSpeed.Teta() * angularSpeedCoefficient);

    agent->appliedLocalSpeed = agent->appliedGlobalSpeed;
    agent->appliedLocalSpeed.rotate( -1 * agent->robot->orien());

    buildAndSendPacket(agent->getID(), agent->appliedLocalSpeed);
}
