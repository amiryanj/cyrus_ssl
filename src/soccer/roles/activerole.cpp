#include "activerole.h"

ActiveRole::ActiveRole()
{
    m_type = SSLRole::e_Active;

    m_hardness = 2;
}

void ActiveRole::run()
{
    assert(m_agent != NULL);
    assert(!m_agent->isNull());
    if(analyzer->canKick(m_agent->robot)) {
        m_state = e_CanKick;
    }

    else {
        float distToBall = (m_agent->robot->Position().to2D() - world->mainBall()->Position()).lenght();
        if(distToBall < 250)
            m_state = e_NearBall;
        else if(distToBall > 350)
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

Vector2D ActiveRole::expectedPosition()
{
    return SSLSkill::KickStylePosition(world->mainBall()->Position(),
                                        SSLSkill::opponentPenaltyPoint()).to2D();
}
