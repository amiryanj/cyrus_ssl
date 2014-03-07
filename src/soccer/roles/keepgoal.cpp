#include "keepgoal.h"

KeepGoal::KeepGoal()
{
}

GoalState KeepGoal::run()
{
    SSLWorldModel* worldModel = SSLWorldModel::getInstance();
    SSLGame* game = SSLGame::getInstance();

    Station myTarget;
    myTarget.setPosition(Vector3D(0, 100, 0));
    this->target.goal_point.set(myTarget);
//    this->getTarget()->position.setY(worldModel->ball->Position().Y());
//    this->getTarget()->velocity = 0;
////    this->getTarget()->heading =


    return this->target;
}
