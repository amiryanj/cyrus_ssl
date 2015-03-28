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

