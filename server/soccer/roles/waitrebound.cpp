#include "waitrebound.h"

WaitRebound::WaitRebound()
{
    this->m_type = SSLRole::e_WaitRebound;

    m_hardness = 2;
}

Vector3D WaitRebound::getBestPosition() const
{
    return m_bestPosition;
}

void WaitRebound::setBestPosition(const Vector3D &value)
{
    m_bestPosition = value;
}

Vector3D WaitRebound::expectedPosition()
{
    return SSL::Position::opponentMidfieldUpPosition();
}

void WaitRebound::run()
{
    Vector3D target = SSL::Position::opponentMidfieldUpPosition();
    Vector3D tolerance(100, 100, M_PI/4);
    SSLSkill::goToPointWithPlanner(m_agent, target, tolerance, true);
}
