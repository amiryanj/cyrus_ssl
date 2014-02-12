#include "sslagent.h"

SSLAgent::SSLAgent()
{    
}

SSLAgent::~SSLAgent()
{
}

bool SSLAgent::isNull()
{
    return !(this->realRobot->isInField);
}

int SSLAgent::getID() const
{
    if(this->realRobot == NULL)
    {
        std::cerr << "*** The Agent has NO ROBOT ***" << std::endl;
        return -1;
    }
    return this->realRobot->id;
}

void SSLAgent::run()
{
    if(this->role == NULL)
    {
        std::cerr << "*** The Agent has NO ROLE ***" << std::endl;
        return;
    }

    if(this->realRobot == NULL)
    {
        std::cerr << "*** The Agent has NO ROBOT Assigned ***" << std::endl;
        return;
    }

//    this->target = this->role->run();
}
