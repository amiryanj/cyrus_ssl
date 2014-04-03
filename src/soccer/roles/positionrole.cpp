#include "positionrole.h"

PositionRole::PositionRole()
{
    this->m_type = SSLRole::e_Position;

    m_hardness = 2;
}

Vector2D PositionRole::expectedPosition()
{
    return m_position.to2D();
}

void PositionRole::run()
{
    SSLSkill::goToPointWithPlanner(m_agent, m_position, m_tolerance, true);
}

Vector3D PositionRole::getPosition() const
{
    return m_position;
}

void PositionRole::setPosition(const Vector3D &value)
{
    m_position = value;
}

Vector3D PositionRole::getTolerance() const
{
    return m_tolerance;
}

void PositionRole::setTolerance(const Vector3D &value)
{
    m_tolerance = value;
}
