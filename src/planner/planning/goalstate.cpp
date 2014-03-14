#include "goalstate.h"
#include <cmath>
using namespace std;
GoalState::GoalState()
{
}

GoalState &GoalState::operator =(GoalState other)
{
    this->goal_point = other.goal_point;
    this->tolerance = other.tolerance;
    return *this;
}

double GoalState::minDistTo(Station p)
{
    Vector3D A(goal_point.position - tolerance.position);
    Vector3D B(goal_point.position + tolerance.position);
    double dx = fabs(p.position.X() - goal_point.position.X());
    dx -= tolerance.position.X();
    if(dx < 0) dx = 0;

    double dy = fabs(p.position.Y() - goal_point.position.Y());
    dy -= tolerance.position.Y();
    if(dy < 0) dy = 0;

    return (sqrt(dx*dx + dy*dy));
}
