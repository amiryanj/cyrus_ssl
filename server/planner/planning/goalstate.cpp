#include "goalstate.h"
#include <cmath>
using namespace std;
GoalState::GoalState()
{
    tolerance.setPosition(Vector3D(0, 0, 0));
}

void GoalState::setTolerance(Station tol)
{
    this->tolerance = tol;
}

GoalState &GoalState::operator =(GoalState other)
{
    this->goal_point = other.goal_point;
    this->tolerance = other.tolerance;
    return *this;
}

double GoalState::minDistTo(const Station &p)
{
    Vector3D A(goal_point.getPosition() - tolerance.getPosition());
    Vector3D B(goal_point.getPosition() + tolerance.getPosition());
    double dx = fabs(p.getPosition().X() - goal_point.getPosition().X());
    dx -= tolerance.getPosition().X();
    if(dx < 0) dx = 0;

    double dy = fabs(p.getPosition().Y() - goal_point.getPosition().Y());
    dy -= tolerance.getPosition().Y();
    if(dy < 0) dy = 0;

    return (sqrt(dx*dx + dy*dy));
}
