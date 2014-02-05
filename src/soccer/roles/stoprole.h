#ifndef STOPROLE_H
#define STOPROLE_H

#include "SSLRole.h"
#include "../planning/state.h"

class StopRole : public SSLRole
{
public:
    StopRole(SSLRobot*);


    Planner::State* run();
};

#endif // STOPROLE_H
