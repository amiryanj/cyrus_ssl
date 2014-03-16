#include "positionrole.h"

PositionRole::PositionRole(SSLAgent *agent)
{
    this->m_agent = agent;
    this->m_type = SSLRole::Position;
}

float PositionRole::getFacing() const
{
    return facing;
}

void PositionRole::setFacing(float value)
{
    facing = value;
}

Vector2D PositionRole::getPosition() const
{
    return position;
}

void PositionRole::setPosition(const Vector2D &value)
{
    position = value;
}

void PositionRole::run()
{

}
