#include "sslrole.h"

SSLRole::SSLRole()
{
    m_state = e_FarFromBall;
}

void SSLRole::setAgent(SSLAgent *agent)
{
    this->m_agent = agent;
}

