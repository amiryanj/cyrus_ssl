#include "waitpass.h"

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
    return SSLSkill::opponentMidfieldDownPosition();
}

void WaitPass::run()
{
    Vector3D target = SSLSkill::KickStylePosition(SSLSkill::opponentMidfieldUpPosition().to2D(),
                                                  SSLSkill::opponentGoalCenter(), 100);
    Vector3D tolerance(100, 100, M_PI/4);
    SSLSkill::goToPointWithPlanner(m_agent, target, tolerance, true);
}
