#ifndef KEEPGOAL_H
#define KEEPGOAL_H

#include "SSLRole.h"
#include "../ai/SSLWorldModel.h"
#include "../ai/SSLGame.h"
#include "../definition/Concepts.h"

class KeepGoal : public SSLRole
{
public:
    KeepGoal();

    GoalState run();

private:


};

#endif // KEEPGOAL_H
