#include "waitpass.h"
#include "../../definition/SSLTeam.h"

WaitPass::WaitPass()
{
    this->m_type = SSLRole::e_WaitPass;    

    m_hardness = 2;
}

Vector3D WaitPass::getBestPosition() const
{
    return m_bestPosition;
}

void WaitPass::setBestPosition(const Vector3D &value)
{
    m_bestPosition = value;
}

Vector3D WaitPass::expectedPosition()
{
    Vector3D target;
    if(analyzer->isGameRunning()) {
        if(analyzer->ballPossessorTeam()->color == game->ourColor()) {
            target = SSLSkill::opponentMidfieldUpPosition();
        }
        else
            target = SSLSkill::ourMidfieldDownPosition();
    }

    else if(world->m_refereeState == SSLReferee::Stop) {
        target = SSLSkill::wallStandFrontBall(1);
    }

    else { // other restart states
        target = SSLSkill::ourMidfieldCenterPosition();
    }
    return target;
}

void WaitPass::run()
{

    Vector3D tolerance (300, 300, M_PI/4);

    Vector3D target = expectedPosition();

//    Vector3D target(game->ourSide() * (FIELD_LENGTH / 2.0) + 10, 10, 0); // for test invalid goal point
    SSLSkill::goToPointWithPlanner(m_agent, target, tolerance, true);
}
