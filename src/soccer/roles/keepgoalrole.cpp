#include "keepgoalrole.h"

#define worldModel SSLWorldModel::getInstance()
#define game = SSLGame::getInstance()

KeepGoalRole::KeepGoalRole(SSLAgent *agent)
{
    this->m_agent = agent;
    this->m_type = SSLRole::KeepGoal;
}

void KeepGoalRole::run()
{
    Station myTarget;
    myTarget.setPosition(Vector3D(FIELD_LENGTH/2 - 10, 1220, 30 * M_PI/180));
    m_agent->target.goal_point.set(myTarget);
    Station tolerance;
    tolerance.setPosition(Vector3D(100, 100, M_PI/4));
    m_agent->target.tolerance.set(tolerance);

    /*
    void GoalKeeperRole::run() {
    Vector2D goalCenter ((double)0, (double)FIELD_LENGTH / (double)2 * (double)SSLGame::getInstance()->ourSide());
    Vector2D ball = SSLWorldModel::getInstance()->ball->Position();

    if(SSLAnalyzer::getInstance()->canKick(getRobot())){
        SSLSkill::getInstance()->kick(getRobot());
    }

    Vector2D target;
    target.setY(((double)FIELD_LENGTH / (double)2) - (double)ROBOT_RADIUS);
    if(ball.X() == goalCenter.X()){
        target.setX(0);
    }else if(ball.Y() == goalCenter.Y() || abs(ball.Y()) > (double)FIELD_LENGTH/(double)2){
        if(ball.Y() > 0){
            target.setX((double)FIELD_GOAL_WIDTH / (double)2);
        }else{
            target.setX(-1 * (double)FIELD_GOAL_WIDTH / (double)2);
        }
    }else{
        double m = (ball.Y() - goalCenter.Y()) / (ball.X() - goalCenter.X());
        target.setX(((target.Y() - goalCenter.Y()) / m) + goalCenter.X());
    }
    //Heading must set from analyzer:
    SSLSkill::getInstance()->goToPoint(getRobot(), target, 0);

    }
     */
}
