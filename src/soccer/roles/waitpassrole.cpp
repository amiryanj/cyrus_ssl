#include "waitpassrole.h"

WaitPassRole::WaitPassRole(SSLAgent *agent)
{
    this->m_agent = agent;
    this->m_type = SSLRole::WaitPass;
}

Vector3D WaitPassRole::getBestPosition() const
{
    return m_bestPosition;
}

void WaitPassRole::setBestPosition(const Vector3D &value)
{
    m_bestPosition = value;
}

void WaitPassRole::run()
{

}
