#ifndef _GOALSTATE_H
#define _GOALSTATE_H

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

    double minDistTo(const Station &p);
};

#endif // _GOALSTATE_H
