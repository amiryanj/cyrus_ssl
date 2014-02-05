#include "keepgoal.h"

KeepGoal::KeepGoal(SSLRobot* sslRobot):SSLRole(sslRobot)
{
}

Planner::State* KeepGoal::run()
{
    SSLWorldModel* worldModel = SSLWorldModel::getInstance();
    SSLGame* game = SSLGame::getInstance();

    this->getTarget()->position.setX(((FIELD_LENGTH / 2.0) - getRobot()->radius) * game->ourSide());
    this->getTarget()->position.setY(worldModel->ball->Position().Y());
    this->getTarget()->velocity = 0;
//    this->getTarget()->heading =


    return this->target;
}
