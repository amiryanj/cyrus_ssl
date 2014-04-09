#include "activerole.h"

ActiveRole::ActiveRole()
{
    m_type = SSLRole::e_Active;

    m_hardness = 1;
}

void ActiveRole::run()
{
    Vector3D tolerance(ROBOT_RADIUS, ROBOT_RADIUS, M_PI_4);

    if(analyzer->isGameRunning() == false) {  // stop states
        if(world->m_refereeState == SSLReferee::Stop) {
            Vector3D target = SSLSkill::wallStandFrontBall(0);
//            Vector3D target = SSLSkill::DefenseStylePosition(world->mainBall()->Position(), SSLSkill::ourGoalCenter(), 500);
            SSLSkill::goToPointWithPlanner(m_agent, target, tolerance, true, 2*BALL_RADIUS, ROBOT_RADIUS);
        }
        else if(analyzer->isOurKickOffPosition() || analyzer->isOurPenaltyPosition()) {
            Vector3D target = SSLSkill::KickStylePosition(world->mainBall()->Position(), SSLSkill::opponentGoalCenter(), 80);
            SSLSkill::goToPointWithPlanner(m_agent, target, tolerance, true, BALL_RADIUS, ROBOT_RADIUS);
        }
        else if(analyzer->isOurKickOffKick()) { // the robot is ready for kick
            SSLSkill::goAndKick(m_agent, SSLSkill::opponentGoalCenter(), 1);
        }
        else if(analyzer->isOurPenaltyKick()) { // the robot is ready for kick
            SSLSkill::goAndKick(m_agent, SSLSkill::opponentGoalCenter(), 1);
        }
        else if(analyzer->isOurDirectKick() || analyzer->isOurIndirectKick()) {
            Vector3D target = SSLSkill::KickStylePosition(world->mainBall()->Position(), SSLSkill::opponentGoalCenter(), 80);
            if((m_agent->robot->Position() - target).lenght2D() < 100)
                SSLSkill::goAndKick(m_agent, SSLSkill::opponentGoalCenter(), 1);
            else
                SSLSkill::goToPointWithPlanner(m_agent, target, tolerance, true, 2*BALL_RADIUS, ROBOT_RADIUS);
        }
        else if(analyzer->isOpponentKickOffPosition() || analyzer->isOpponentKickOffKick() ||
                analyzer->isOpponentDirectKick() || analyzer->isOpponentIndirectKick() ) {
            Vector3D target = SSLSkill::wallStandFrontBall(0);
            SSLSkill::goToPointWithPlanner(m_agent, target, tolerance, true, BALL_RADIUS, ROBOT_RADIUS);
        }
        else if (analyzer->isOpponentPenaltyPosition() || analyzer->isOpponentPenaltyKick()) {
            Vector3D target = SSLSkill::ourMidfieldUpPosition();
            SSLSkill::goToPointWithPlanner(m_agent, target, tolerance * 2, true, 2*BALL_RADIUS, ROBOT_RADIUS);
        }
        return;
    }

    // ************** game is running *****************************************************
    // if the ball is in our penalty area, the actve player should approach our defense area
    Vector3D target = SSLSkill::KickStylePosition(world->mainBall()->Position(), SSLSkill::opponentGoalCenter(), 80);
    if(analyzer->isPointWithinOurPenaltyArea(target.to2D())) {
        target = SSLSkill::ourMidfieldUpPosition();
        SSLSkill::goToPointWithPlanner(m_agent, target, tolerance, true, 3 * BALL_RADIUS, ROBOT_RADIUS);
    }
    else {
        if(analyzer->canKick(m_agent->robot)) {
            m_state = e_CanKick;
        }

        else {
            float distToTarget = (m_agent->robot->Position().to2D() - target.to2D()).lenght();
            if(distToTarget < 100 ) {
                m_state = e_NearBall;
            }
            else if(distToTarget > 150)
                m_state = e_FarFromBall;
        }

        switch (m_state) {
        case e_CanKick:
            SSLSkill::goAndKick(m_agent, SSLSkill::opponentGoalCenter(), 1);
            break;
        case e_NearBall:
            SSLSkill::goAndKick(m_agent, SSLSkill::opponentGoalCenter(), 1);
            break;
        case e_FarFromBall:
            Vector3D tolerance(ROBOT_RADIUS, ROBOT_RADIUS, M_PI_4);
            SSLSkill::goToPointWithPlanner(m_agent, target, tolerance, true, 2.5 * BALL_RADIUS, ROBOT_RADIUS);
            break;
        }
    }
}

Vector3D ActiveRole::expectedPosition()
{
    return SSLSkill::KickStylePosition(world->mainBall()->Position(), SSLSkill::opponentPenaltyPoint());
}
