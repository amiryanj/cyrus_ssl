#include "goalkeeper.h"
#include "../SSLSkill.h"

GoalKeeper::GoalKeeper()
{
    this->m_type = SSLRole::e_GoalKeeper;

    m_hardness = 0;
}

void GoalKeeper::run()
{
    if(analyzer->isPointWithinOurPenaltyArea(world->mainBall()->Position())) {
        SSLSkill::goAndKick(m_agent, 1); // goAndChip()
    }
    else {
        Vector3D target;
        Vector3D tolerance;
        double distBallFromOurGoal_x = fabs(world->mainBall()->Position().X() -
                                            (game->ourSide() * FIELD_LENGTH/2) ); // [0 - 6050]
        float target_x = game->ourSide() * (FIELD_LENGTH/2 -
                                (ROBOT_RADIUS + (distBallFromOurGoal_x * FIELD_PENALTY_AREA_RADIUS) /FIELD_LENGTH));
        float target_y = (world->mainBall()->Position().Y() /(FIELD_WIDTH /2.0)) * (FIELD_GOAL_WIDTH /2.0);

        float target_teta = (world->mainBall()->Position() - Vector2D(target_x, target_y)).arctan();

        target.set(target_x, target_y, target_teta);
        tolerance.set(50, 50, M_PI_4);

        SSLSkill::goToPoint(m_agent, target, tolerance);
    }

//    myTarget.setPosition(Vector3D(SSLGame::getInstance()->ourSide() * (FIELD_LENGTH/2 - 700), 0, 170 * M_PI/180));
//    m_agent->target.goal_point.set(myTarget);
//    Station tolerance;
//    tolerance.setPosition(Vector3D(100, 100, M_PI/4));
//    m_agent->target.tolerance.set(tolerance);

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

Vector2D GoalKeeper::expectedPosition()
{
    return Vector2D(SSLGame::getInstance()->opponentSide() * (FIELD_LENGTH/2 - ROBOT_RADIUS), 0);
}