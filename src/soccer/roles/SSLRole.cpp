#include "SSLRole.h"

SSLRole::SSLRole(SSLRobot* robot)
{
    this->robot = robot;
    this->target = new Planner::State();
}

SSLRole::~SSLRole()
{
    delete target;
}

SSLRobot* SSLRole::getRobot(){
    return this->robot;
}

Planner::State* SSLRole::getTarget(){
    return this->getTarget();
}
