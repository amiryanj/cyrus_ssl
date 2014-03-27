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
    Vector3D zero(0, 0, 0);

    agent->target.goal_point.position = agent->robot->Position();
    agent->desiredGlobalSpeed = zero;
    agent->appliedLocalSpeed = zero;
    agent->appliedGlobalSpeed = zero;

    buildAndSendPacket(agent->getID(), agent->appliedLocalSpeed);
}

void SSLSkill::goToPoint(SSLAgent *agent, Vector3D target, Vector3D tolerance)
{
    float directSpeedCoefficient = 0.6;
    float angularSpeedCoefficient = 0.0;

    Vector3D diff = target - agent->robot->Position();
    if((fabs(diff.X()) < tolerance.X()) && (fabs(diff.Y()) < tolerance.Y()) && (fabs(diff.Teta()) < tolerance.Teta())) {
        halt(agent);
    }
    else {
        diff.normalize2D();

        agent->desiredGlobalSpeed = diff;

        agent->appliedGlobalSpeed = agent->desiredGlobalSpeed; // because controller is not working yet

        agent->appliedLocalSpeed = agent->appliedGlobalSpeed;
        agent->appliedLocalSpeed.rotate( -1 * agent->robot->orien());

        agent->appliedLocalSpeed *= directSpeedCoefficient;

        agent->appliedLocalSpeed.setTeta(agent->appliedLocalSpeed.Teta() * angularSpeedCoefficient);

        buildAndSendPacket(agent->getID(), agent->appliedLocalSpeed);
    }

}

void SSLSkill::goToPointWithPlanner(SSLAgent* agent, Vector3D target, Vector3D tolerance,
                                    bool considerPenaltyArea, short ball_ob_radius, short robot_ob_radius)
{
    cout << "Hello... Go to point with planner" << endl;

    Station init_state;
    init_state.setPosition(agent->robot->Position());
    init_state.setVelocity(agent->robot->Speed());

    agent->planner.setInitialState(init_state);
    GoalState goal;
    goal.goal_point.position = target;
    goal.tolerance.position = tolerance;
    agent->planner.setGoalRegion(goal);

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

    Vector3D nextTarget;
    if(agent->planner.planningResult)
        nextTarget = agent->planner.getTrajectory().getStation(1).position;

    goToPoint(agent, nextTarget, Vector3D(0,0,0));

//    agent->desiredGlobalSpeed = agent->planner.getControl(0);

//    cout << "Desired vel for robot #" << agent->getID() << " is: X= " << agent->desiredGlobalSpeed.X()
//         << " Y= " << agent->desiredGlobalSpeed.Y()
//         << " teta=" << agent->desiredGlobalSpeed.Teta() << endl;

////        temp_applied_vel_global = controller.getControl() / 2000;
//    agent->appliedGlobalSpeed = agent->desiredGlobalSpeed; // because controller is not working yet

//    agent->appliedLocalSpeed = agent->appliedGlobalSpeed;
//    agent->appliedLocalSpeed.rotate(-agent->robot->orien());

//    agent->appliedLocalSpeed *= .6;
//    agent->appliedLocalSpeed.setTeta(agent->appliedLocalSpeed.Teta()*0.0);

//    buildAndSendPacket(agent->getID(), agent->appliedLocalSpeed);

}


// this function is responsible for approaching the ball
// and setting the orientation such that it can kick the ball
// TO DO:
// it should get the target to shoot
void SSLSkill::goAndKick(SSLAgent *agent, double kickStrenghtNormal)
{
    if(analyzer->canKick(agent->robot)) {
        Vector3D speed(1, 0, 0);
        buildAndSendPacket(agent->getID(), speed, kickStrenghtNormal);
    }
    else {
        Vector3D target = KickStylePosition(SSLWorldModel::getInstance()->mainBall()->Position(), opponentGoalCenter());
        goToPoint(agent, target, Vector3D(50, 50, M_PI_4));
    }
}

void SSLSkill::goAndChip(SSLAgent *agent, double chipStrenghtNormal)
{

}

void SSLSkill::buildAndSendPacket(int id, Vector3D &vel, float kickPower)
{
    RobotCommandPacket pkt(vel, true, kickPower);

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

Vector3D SSLSkill::KickStylePosition(Vector2D point, Vector2D target)
{
    Vector2D dir = (target - point).normalized();
    float orien = dir.arctan();
    Vector3D pos(point - dir * (BALL_RADIUS + ROBOT_RADIUS + 100), orien);
}
