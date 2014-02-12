#include "SSLRole.h"

SSLRole::SSLRole(SSLRobot* robot)
{
    this->robot = robot;
}

SSLRole::~SSLRole()
{
//    delete target;
}

SSLRobot* SSLRole::getRobot(){
    return this->robot;
}

GoalState SSLRole::getTarget(){
    return this->target;
}
