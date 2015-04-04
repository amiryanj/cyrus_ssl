#include "sslrole.h"
#include "sslagent.h"

SSLRole::SSLRole()
{
    m_state = e_FarFromBall;
}

void SSLRole::setAgent(SSLAgent *agent)
{
    this->m_agent = agent;
}

bool SSLRole::Halt()
{
    m_agent->skill->halt();
    return true;
}

Vector3D SSLRole::myPosition()
{
    if(m_agent->isNull())
        return Vector3D();
    return m_agent->robot->Position();
}

