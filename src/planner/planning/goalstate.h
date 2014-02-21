#ifndef GOALSTATE_H
#define GOALSTATE_H

#include "station.h"

class GoalState
{
public:
    GoalState();
    Station goal_point;

    Station tolerance;
    void setTolerance(Station tol);

    void setMax(Station max);
    void setMin(Station min);
    void setRadius(double rad);

    GoalState& operator =(GoalState other);
};

#endif // GOALSTATE_H
