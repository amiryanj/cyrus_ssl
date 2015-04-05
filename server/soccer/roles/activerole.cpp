#include "activerole.h"
#include "../sslagent.h"

ActiveRole::ActiveRole()
{
    m_type = SSLRole::e_Active;

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
    if(analyzer->isPointWithinOurPenaltyArea(target.to2D())) {
        target = SSL::Position::ourMidfieldUpPosition();
        m_agent->skill->goToPointWithPlanner(target, tolerance, true, 2.0 * BALL_RADIUS, ROBOT_RADIUS);
    }
    else {
        if(analyzer->canKick(m_agent->robot)) {
            m_state = e_CanKick;
        }

        else {
//            float distToTarget = (m_agent->robot->Position().to2D() - target.to2D()).lenght();
//            if(distToTarget < 180 )
            if(fabs(m_agent->robot->Position().Y() - target.Y()) < 80
                    && fabs(m_agent->robot->Position().X() - target.X()) < 100)
                m_state = e_NearBall;            
            else // if(distToTarget > 150)
                m_state = e_FarFromBall;
        }

        m_agent->skill->goAndKick(Ball_Position, SSL::Position::opponentGoalCenter(), 1);
//        switch (m_state) {
//        case e_CanKick:
//            m_agent->skill->goAndKick(Ball_Position, SSL::Position::opponentGoalCenter(), 1);
//            break;
//        case e_NearBall:
//            m_agent->skill->goAndKick(Ball_Position, SSL::Position::opponentGoalCenter(), 1);
//            break;
//        case e_FarFromBall:
//            Vector3D tolerance(ROBOT_RADIUS/2, ROBOT_RADIUS/2, M_PI_4);
//            m_agent->skill->goToPointWithPlanner(target, tolerance, true, 2.0 * BALL_RADIUS, ROBOT_RADIUS);
//            break;
//        }
    }
}

Vector3D ActiveRole::expectedPosition()
{
    return SSL::Position::KickStylePosition(world->mainBall()->Position(),
                                            SSL::Position::opponentPenaltyPoint(), 100);
}
