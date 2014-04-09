#include "goalkeeper.h"
#include "../SSLSkill.h"

GoalKeeper::GoalKeeper()
{
    this->m_type = SSLRole::e_GoalKeeper;

    m_hardness = 0;
}

void GoalKeeper::run()
{
    Vector3D tolerance(30, 30, M_PI_4);
    if(analyzer->isOpponentPenaltyPosition()) {
        Vector3D target = SSLSkill::wallStandFrontBall(0);
        SSLSkill::goToPoint(m_agent, target, tolerance);
    }

    else if(analyzer->isOpponentPenaltyKick()) {
        Vector3D target = SSLSkill::wallStandFrontBall(0);
        SSLSkill::goToPoint(m_agent, target, tolerance);
    }

    else if(analyzer->isPointWithinOurPenaltyArea(world->mainBall()->Position())) {
        SSLSkill::goAndKick(m_agent, SSLSkill::opponentGoalCenter(), 1); // goAndChip()
    }

    else if(analyzer->isPointWithinOurCorner(world->mainBall()->Position()))
//            && (world->m_refereeState == SSLReferee::Stop || analyzer->isOpponentDirectKick() || analyzer->isOpponentIndirectKick()))
    {
        SSLRobot* near_goalie_robot = analyzer->nearestToPoint(game->opponentTeam()->inFields(), SSLSkill::ourGoalCenter());
        if(near_goalie_robot != NULL) {
            Vector2D diff = near_goalie_robot->Position().to2D() - SSLSkill::ourGoalCenter();
            diff.normalize();
            diff *= 500;
            Vector3D target = (diff + SSLSkill::ourGoalCenter()).to3D();
            target = SSLSkill::DefenseStylePosition(target.to2D(), SSLSkill::ourGoalCenter(), 30);
            SSLSkill::goToPoint(m_agent, target, tolerance);
            return;
        }
    }
//        if(analyzer->isPoint)
//        Vector3D target = SSLSkill::

//    else if(analyzer->isOpponentDirectKick() || analyzer->isOpponentIndirectKick()) {

//    }

    else { // normal play
        Vector3D target;

        SSLRobot* near_goalie_robot = analyzer->nearestToPoint(game->opponentTeam()->inFields(), SSLSkill::ourGoalCenter());
        if(near_goalie_robot != NULL) {
            if(analyzer->isPointWithinOurPenaltyArea(near_goalie_robot->Position().to2D())) {
                target = SSLSkill::DefenseStylePosition(near_goalie_robot->Position().to2D(), SSLSkill::ourGoalCenter(), -50);
                SSLSkill::goToPoint(m_agent, target, tolerance);
                return;
            }
        }

        // else

        double distBallFromOurGoal_x = fabs(world->mainBall()->Position().X() -
                                            (game->ourSide() * FIELD_LENGTH/2) ); // [0 - 6050]
        float target_x = game->ourSide() * (FIELD_LENGTH/2 -
                                (ROBOT_RADIUS * 0.8 + (distBallFromOurGoal_x * FIELD_PENALTY_AREA_RADIUS * 0.4) /FIELD_LENGTH));

        float target_y;
        if(fabs(world->mainBall()->Position().Y()) < 500 )
            target_y = (world->mainBall()->Position().Y() /(FIELD_WIDTH /2.0)) * (FIELD_GOAL_WIDTH /2.0);
        else if(world->mainBall()->Position().Y() > 0){
            target_y = FIELD_GOAL_WIDTH / 2 - ROBOT_RADIUS + 20;
        }
        else {
            target_y = -(FIELD_GOAL_WIDTH / 2 - ROBOT_RADIUS + 30);
        }

        float target_teta = (world->mainBall()->Position() - Vector2D(target_x, target_y)).arctan();

        target.set(target_x, target_y, target_teta);

        SSLSkill::goToPoint(m_agent, target, tolerance);
        return;
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

Vector3D GoalKeeper::expectedPosition()
{
    return SSLSkill::ourGoalCenter().to3D();
}
