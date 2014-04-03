#include "SSLBall.h"

SSLBall::SSLBall()
{
    this->m_radius = 220;
}

void SSLBall::setFilteredSpeed(const Vector2D &speed)
{
    m_filteredSpeed = speed;
}

Vector2D SSLBall::getFilteredSpeed() const
{
    return m_filteredSpeed;
}

