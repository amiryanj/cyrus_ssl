#include "activerole.h"
#include "../sslagent.h"

ActiveRole::ActiveRole(int index_)
{
    m_type = SSLRole::e_Active;
    this->m_index = index_;

    m_hardness = 1;
}

void ActiveRole::run()
{
    Vector3D tolerance(ROBOT_RADIUS, ROBOT_RADIUS/2, M_PI / 6.0);

    if(analyzer->isGameRunning() == false) {  // stop states
        if(world->m_refereeState == SSLReferee::Stop) {
            Vector3D target = SSL::Position::wallStandFrontBall(0, world->mainBall()->Position());
//            Vector3D target = SSLSkill::DefenseStylePosition(world->mainBall()->Position(), SSLSkill::ourGoalCenter(), 500);
            m_agent->skill->goToPointWithPlanner(target, tolerance, true, 1.3*BALL_RADIUS, ROBOT_RADIUS);
        }
        else if(analyzer->isOurKickOffPosition() || analyzer->isOurPenaltyPosition()) {
            Vector3D target = SSL::Position::KickStylePosition(world->mainBall()->Position(),
                                                               SSL::Position::opponentGoalCenter(), 80);
            m_agent->skill->goToPointWithPlanner(target, tolerance, true, BALL_RADIUS, ROBOT_RADIUS);
        }
        else if(analyzer->isOurKickOffKick()) { // the robot is ready for kick
            m_agent->skill->goAndKick(Ball_Position, SSL::Position::opponentGoalCenter(), 1);
        }
        else if(analyzer->isOurPenaltyKick()) { // the robot is ready for kick
            m_agent->skill->goAndKick(Ball_Position, SSL::Position::opponentGoalCenter(), 1);
        }
        else if(analyzer->isOurDirectKick() || analyzer->isOurIndirectKick()) {
            Vector3D target = SSL::Position::KickStylePosition(world->mainBall()->Position(),
                                                               SSL::Position::opponentGoalCenter(), 80);
            if((m_agent->robot->Position() - target).lenght2D() < 100)
                m_agent->skill->goAndKick(Ball_Position, SSL::Position::opponentGoalCenter(), 1);
            else
                m_agent->skill->goToPointWithPlanner(target, tolerance, true, 2*BALL_RADIUS, ROBOT_RADIUS);
        }
        else if(analyzer->isOpponentKickOffPosition() || analyzer->isOpponentKickOffKick() ||
                analyzer->isOpponentDirectKick() || analyzer->isOpponentIndirectKick() ) {
            Vector3D target = SSL::Position::wallStandFrontBall(0, world->mainBall()->Position());
            m_agent->skill->goToPointWithPlanner(target, tolerance, true, BALL_RADIUS, ROBOT_RADIUS);
        }
        else if (analyzer->isOpponentPenaltyPosition() || analyzer->isOpponentPenaltyKick()) {
            Vector3D target = SSL::Position::ourMidfieldUpPosition();
            m_agent->skill->goToPointWithPlanner(target, tolerance * 2, true, 2*BALL_RADIUS, ROBOT_RADIUS);
        }
        return;
    }

    // ************** game is running *****************************************************
    // if the ball is in our penalty area, the actve player should approach our defense area
    Vector3D target = SSL::Position::KickStylePosition(world->mainBall()->Position(),
                                                       SSL::Position::opponentGoalCenter(), 100);
    if(analyzer->isPointWithinOurPenaltyArea(target.to2D()))  {
        target = SSL::Position::ourMidfieldUpPosition();
        m_agent->skill->goToPointWithPlanner(target, tolerance, true, 2.0 * BALL_RADIUS, ROBOT_RADIUS);
    }
    else if((world->mainBall()->Position() - SSL::Position::ourGoalCenter()).lenght() < 4000) {
        SSLRobot* op_nearest = analyzer->nearestToBall(game->opponentTeam()->getInFieldRobots());
        if(op_nearest != NULL) {
            if((op_nearest->Position().to2D() - Ball_Position).lenght() > 400 ) {
                Vector2D kick_out = Ball_Position +
                                    (Ball_Position - SSL::Position::ourGoalCenter()).normalized() * 1000;
                m_agent->skill->goAndKick(Ball_Position, kick_out, 1);
                return;
            }
        }
    }

    m_agent->skill->goAndKick(Ball_Position, SSL::Position::opponentGoalCenter(), 1);



}

Vector3D ActiveRole::expectedPosition()
{
    return SSL::Position::KickStylePosition(world->mainBall()->Position(),
                                            SSL::Position::opponentPenaltyPoint(), 100);
}
