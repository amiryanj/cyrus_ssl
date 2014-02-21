#include "SSLRole.h"

SSLRole::SSLRole()
{
}

SSLRole::~SSLRole()
{
//    delete target;
}

SSLRobot* SSLRole::getRobot(){
    return this->robot;
}

void SSLRole::setRobot(SSLRobot *r)
{
    this->robot = r;
}

GoalState SSLRole::getTarget(){
    return this->target;
}
