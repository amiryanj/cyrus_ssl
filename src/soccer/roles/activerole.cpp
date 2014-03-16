#include "activerole.h"

ActiveRole::ActiveRole(SSLAgent *agent)
{
    this->m_agent = agent;
    this->m_type = SSLRole::Active;

}

void ActiveRole::run()
{


}
