#include "keepgoal.h"

KeepGoal::KeepGoal()
{
}

GoalState KeepGoal::run()
{
    SSLWorldModel* worldModel = SSLWorldModel::getInstance();
    SSLGame* game = SSLGame::getInstance();

    Station myTarget;
    myTarget.setPosition(Vector3D(FIELD_LENGTH/2 - 10, 1220, 30 * M_PI/180));
    this->target.goal_point.set(myTarget);
    Station tolerance;
    tolerance.setPosition(Vector3D(100, 100, M_PI/4));
    this->target.tolerance.set(tolerance);

//    this->getTarget()->position.setY(worldModel->ball->Position().Y());
//    this->getTarget()->velocity = 0;
////    this->getTarget()->heading =

    return this->target;
}
