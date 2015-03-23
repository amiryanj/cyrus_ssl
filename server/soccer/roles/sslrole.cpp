#include "sslrole.h"
#include "../../definition/sslagent.h"

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
    SSLSkill::halt(m_agent);
    return true;
}

