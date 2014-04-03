#include "activerole.h"

ActiveRole::ActiveRole()
{
    m_type = SSLRole::e_Active;

    m_hardness = 2;
}

void ActiveRole::run()
{
    Vector3D tolerance(2*ROBOT_RADIUS, 2*ROBOT_RADIUS, M_PI_4);
    if(analyzer->isGameRunning()) {
        cout << "game is in running mode (analyzer)" << endl;
    }

    if(analyzer->isGameRunning() == false) {  // stop states
        if(world->m_refereeState == SSLReferee::Stop) {
            Vector3D target = SSLSkill::KickStylePosition(world->mainBall()->Position(), SSLSkill::opponentGoalCenter(), 500);
            SSLSkill::goToPointWithPlanner(m_agent, target, tolerance, true, BALL_RADIUS, ROBOT_RADIUS);
        }
        if(analyzer->isOurKickOffPosition() || analyzer->isOurPenaltyPosition()) {
            Vector3D target = SSLSkill::KickStylePosition(world->mainBall()->Position(), SSLSkill::opponentGoalCenter(), 200);
            SSLSkill::goToPointWithPlanner(m_agent, target, tolerance, true, BALL_RADIUS, ROBOT_RADIUS);
        }
        else if(analyzer->isOurDirectKick() || analyzer->isOurIndirectKick()) {
            SSLSkill::goAndKick(m_agent, 1);
        }
        else if(analyzer->isOurKickOffKick()) {
            SSLSkill::goAndKick(m_agent, 1);
        }
        else if(analyzer->isOurPenaltyKick()) {
            SSLSkill::goAndKick(m_agent, 1);
        }
        else if(analyzer->isOpponentKickOffPosition() || analyzer->isOpponentKickOffKick() ||
                analyzer->isOpponentDirectKick() || analyzer->isOpponentIndirectKick() ) {
            Vector3D target = SSLSkill::KickStylePosition(world->mainBall()->Position(), SSLSkill::opponentGoalCenter(), 500);
            SSLSkill::goToPointWithPlanner(m_agent, target, tolerance, true, BALL_RADIUS, ROBOT_RADIUS);
        }
        else if (analyzer->isOpponentPenaltyPosition() || analyzer->isOpponentPenaltyKick()) {
            Vector3D target = SSLSkill::ourMidfieldDownPosition();
            SSLSkill::goToPointWithPlanner(m_agent, target, tolerance, true, BALL_RADIUS, ROBOT_RADIUS);
        }
        return;
    }

    if(analyzer->canKick(m_agent->robot)) {
        m_state = e_CanKick;
    }

    else {
        float distToBall = (m_agent->robot->Position().to2D() - world->mainBall()->Position()).lenght();
        if(distToBall < 450)
            m_state = e_NearBall;
        else if(distToBall > 650)
            m_state = e_FarFromBall;

    }

    switch (m_state) {
    case e_CanKick:
        SSLSkill::goAndKick(m_agent, 1);
        break;
    case e_NearBall:
        SSLSkill::goAndKick(m_agent, 1);
        break;
    case e_FarFromBall:
        Vector3D target = SSLSkill::KickStylePosition(world->mainBall()->Position(), SSLSkill::opponentGoalCenter());
        Vector3D tolerance(2*ROBOT_RADIUS, 2*ROBOT_RADIUS, M_PI_4);
        SSLSkill::goToPointWithPlanner(m_agent, target, tolerance, true, BALL_RADIUS, ROBOT_RADIUS);
        break;    
    }
}

Vector3D ActiveRole::expectedPosition()
{
    return SSLSkill::KickStylePosition(world->mainBall()->Position(), SSLSkill::opponentPenaltyPoint());
}
