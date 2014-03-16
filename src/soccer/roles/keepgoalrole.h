#ifndef KEEPGOAL_H
#define KEEPGOAL_H

#include "sslrole.h"
#include "../../ai/SSLWorldModel.h"
#include "../../ai/SSLGame.h"
#include "../../definition/Concepts.h"

class KeepGoalRole : public SSLRole
{
public:
    KeepGoalRole(SSLAgent* agent);

    void run();

private:


};

#endif // KEEPGOAL_H
