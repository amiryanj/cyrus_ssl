#include "sslagent.h"

SSLAgent::SSLAgent()
{
}

bool SSLAgent::isNull()
{
    return !(this->robot->isInField);
}

int SSLAgent::getID() const
{
    if(this->robot == NULL)
    {
        std::cerr << "*** The Agent has NO ROBOT ***" << std::endl;
        return -1;
    }
    return this->robot->id;
}

void SSLAgent::run()
{
    if(this->role == NULL)
    {
        std::cerr << "*** The Agent has NO ROLE ***" << std::endl;
        return;
    }

    if(this->robot == NULL)
    {
        std::cerr << "*** The Agent has NO ROBOT Assigned ***" << std::endl;
        return;
    }

    this->role->run();
}
