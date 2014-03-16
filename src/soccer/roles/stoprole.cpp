#include "stoprole.h"

StopRole::StopRole(SSLAgent *agent)
{
    this->m_agent = agent;
    this->m_type = SSLRole::Stop;
}

void StopRole::run()
{

//    this->getTarget()->position.setX(this->getRobot()->Position().X());
//    this->getTarget()->position.setY(this->getRobot()->Position().Y());
//    this->getTarget()->velocity = 0.0;
//    this->getTarget()->heading = this->getRobot()->orien();

//    return this->getTarget();
}
