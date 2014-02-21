#ifndef STOPROLE_H
#define STOPROLE_H

#include "SSLRole.h"

class StopRole : public SSLRole
{
public:
    StopRole();

    GoalState run();
};

#endif // STOPROLE_H
