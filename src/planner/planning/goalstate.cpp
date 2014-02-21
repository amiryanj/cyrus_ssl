#include "goalstate.h"

GoalState::GoalState()
{
}

GoalState &GoalState::operator =(GoalState other)
{
    this->goal_point = other.goal_point;
    this->tolerance = other.tolerance;
    return *this;
}
