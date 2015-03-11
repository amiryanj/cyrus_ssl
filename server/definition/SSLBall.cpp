#include "SSLBall.h"
#include "../ai/SSLWorldModel.h"

SSLBall *SSLBall::mainBall()
{
    return SSLWorldModel::getInstance()->mainBall();
}

SSLBall::SSLBall()
{
    this->m_radius = 22;
    this->m_isStopped = true;
}

//void SSLBall::setFilteredSpeed(const Vector2D &speed)
//{
//    m_filteredSpeed = speed;
//}

//Vector2D SSLBall::getFilteredSpeed() const
//{
//    return m_filteredSpeed;
//}

bool SSLBall::isStopped() const
{
    return m_isStopped;
}

void SSLBall::setStopped(bool stopped)
{
    m_isStopped =  stopped;
}

