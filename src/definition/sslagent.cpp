#include "sslagent.h"

SSLAgent::SSLAgent()
{
}

bool SSLAgent::isNull()
{
    return !(this->robot->isInField);
}
