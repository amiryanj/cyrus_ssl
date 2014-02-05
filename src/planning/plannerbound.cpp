#include "plannerbound.h"

using namespace Planner;

PlannerBound::PlannerBound()
{
    this->topBound = INFINITY;
    this->downBound = -INFINITY;
    this->rightBound = INFINITY;
    this->leftBound = -INFINITY;
}

PlannerBound::PlannerBound(double left, double down, double right, double top)
{
    this->set(left, down, right, top);
}

void PlannerBound::set(double left, double down, double right, double top)
{
    this->topBound = top;
    this->downBound = down;
    this->rightBound = right;
    this->leftBound = left;
}

void PlannerBound::set(Vector2D downLeft, Vector2D topRight)
{
    this->leftBound = downLeft.X();
    this->downBound = downLeft.Y();
    this->rightBound = topRight.X();
    this->topBound = topRight.Y();
}

bool PlannerBound::isEmpty()
{
    if(this->topBound == this->downBound || this->rightBound == this->leftBound)
        return true;
    return false;
}

Vector2D PlannerBound::getTopLeft()
{
    Vector2D v(leftBound, topBound);
    return v;
}

Vector2D PlannerBound::getTopRight()
{
    Vector2D v(rightBound, topBound);
    return v;
}

Vector2D PlannerBound::getDownLeft()
{
    Vector2D v(leftBound, downBound);
    return v;
}

Vector2D PlannerBound::getDownRight()
{
    Vector2D v(rightBound, downBound);
    return v;

}
