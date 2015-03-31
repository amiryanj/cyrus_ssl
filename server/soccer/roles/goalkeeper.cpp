#include "goalkeeper.h"
#include "../../../common/math/linesegment.h"
#include "../../definition/SSLTeam.h"
#include "../../definition/SSLRobot.h"
#include "../sslskill.h"
#include "../sslagent.h"

GoalKeeper::GoalKeeper()
{
    this->m_type = SSLRole::e_GoalKeeper;

    m_hardness = 0;
}

void GoalKeeper::run()
{
    if( analyzer->isOpponentPenaltyPosition() ) {
        Vector3D target = SSL::Position::goalKeeperPosition(0.03f, 0.0f, world->mainBall()->Position());
        m_agent->skill->goToPoint(target);
    }

    else if(analyzer->isOpponentPenaltyKick()) {
        Vector3D target = SSL::Position::goalKeeperPosition(0.03f, 0.0f, world->mainBall()->Position());;

        SSLAnalyzer::RobotIntersectTime op_penalty_kicker =
                analyzer->nearestRobotToPoint(game->opponentColor(), SSL::Position::ourPenaltyPoint());
        if(op_penalty_kicker.isValid())
        {
            float op_orien = op_penalty_kicker.m_robot->orien();
            Vector2D p1 = op_penalty_kicker.m_robot->Position().to2D();
            Vector2D p2 = p1 + Vector2D::unitVector(op_orien) * FIELD_LENGTH;

            LineSegment l1(p1, p2);
            LineSegment l2 = SSL::Position::ourGoalLine();

            Vector2D intersection_pnt = LineSegment::intersection(l1, l2);
            if(intersection_pnt.X() != INFINITY) {
                intersection_pnt.setY( SSL::bound(intersection_pnt.Y(),
                                                  -FIELD_GOAL_WIDTH/2,
                                                   FIELD_GOAL_WIDTH/2 ) );
                target = SSL::Position::goalKeeperPosition(0.0,
                                                           intersection_pnt.Y()/(FIELD_GOAL_WIDTH/2 - ROBOT_RADIUS),
                                                           world->mainBall()->Position());

            }
        }
        m_agent->skill->goToPoint(target);
    }

    else if(analyzer->isPointWithinOurPenaltyArea(world->mainBall()->Position())) {
        m_agent->skill->goAndKick(SSL::Position::opponentGoalCenter(), 1); // goAndChip()
    }

    else if(analyzer->isPointWithinOurCorner(world->mainBall()->Position()))
//            && (world->m_refereeState == SSLReferee::Stop || analyzer->isOpponentDirectKick() || analyzer->isOpponentIndirectKick()))
    {
        SSLRobot* near_goalie_robot = analyzer->nearestToPoint(game->opponentTeam()->getInFieldRobots(),
                                                               SSL::Position::ourGoalCenter());
        if(near_goalie_robot != NULL) {
            Vector2D diff = near_goalie_robot->Position().to2D()
                    - SSL::Position::ourGoalCenter();
            diff.normalize();
            diff *= 500;
            Vector3D target = (diff + SSL::Position::ourGoalCenter()).to3D();
            target = SSL::Position::DefenseStylePosition(target.to2D(),
                                                         SSL::Position::ourGoalCenter(), 30);
            m_agent->skill->goToPoint(target);
            return;
        }
    }
//        if(analyzer->isPoint)
//        Vector3D target = SSLSkill::

//    else if(analyzer->isOpponentDirectKick() || analyzer->isOpponentIndirectKick()) {

//    }

    else { // normal play
        Vector3D target;

        SSLRobot* near_goalie_robot = analyzer->nearestToPoint(game->opponentTeam()->getInFieldRobots(),
                                                               SSL::Position::ourGoalCenter());
        if(near_goalie_robot != NULL) {
            if(analyzer->isPointWithinOurPenaltyArea(near_goalie_robot->Position().to2D())) {
                target = SSL::Position::DefenseStylePosition(near_goalie_robot->Position().to2D(),
                                                        SSL::Position::ourGoalCenter(), -50);
                m_agent->skill->goToPoint(target);
                return;
            }
        }

        // else
        Vector2D ball_target = world->mainBall()->Position();

        SSLAnalyzer::RobotIntersectTime ball_intersect = analyzer->whenWhereCanRobotCatchTheBall(m_agent->robot);
        if(ball_intersect.isValid()) {
            ball_target = ball_intersect.m_position;
        }

        double distBallFromOurGoal_x = fabs(ball_target.X() -
                                            (game->ourSide() * FIELD_LENGTH/2) ); // [0 - 6050]
        float target_x = game->ourSide() * (FIELD_LENGTH/2 -
                                (ROBOT_RADIUS * 0.8 + (distBallFromOurGoal_x * FIELD_PENALTY_AREA_RADIUS * 0.4) /FIELD_LENGTH));

        float target_y;
        if(fabs(ball_target.Y()) < 500 )
            target_y = (ball_target.Y() /(FIELD_WIDTH /2.0)) * (FIELD_GOAL_WIDTH /2.0);
        else if(ball_target.Y() > 0){
            target_y = FIELD_GOAL_WIDTH / 2 - ROBOT_RADIUS + 20;
        }
        else {
            target_y = -(FIELD_GOAL_WIDTH / 2 - ROBOT_RADIUS + 30);
        }

        float target_teta  = - game->ourSide() * M_PI + M_PI_4; //= (ball_target - Vector2D(target_x, target_y)).arctan();

        target.set(target_x, target_y, target_teta);

        m_agent->skill->goToPoint(target);
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
    return SSL::Position::ourGoalCenter().to3D();
}
