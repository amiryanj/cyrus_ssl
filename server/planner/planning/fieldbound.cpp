#include "fieldbound.h"

FieldBound::FieldBound()
{
    this->topBound = INFINITY;
    this->downBound = -INFINITY;
    this->rightBound = INFINITY;
    this->leftBound = -INFINITY;
}

FieldBound::FieldBound(double left, double right, double down, double top)
{
    this->set(left, right, down, top);
}

void FieldBound::set(double left, double right, double down, double top)
{
    this->topBound = top;
    this->downBound = down;
    this->rightBound = right;
    this->leftBound = left;
}

void FieldBound::set(Vector2D downLeft, Vector2D topRight)
{
    this->leftBound = downLeft.X();
    this->downBound = downLeft.Y();
    this->rightBound = topRight.X();
    this->topBound = topRight.Y();
}

bool FieldBound::isEmpty()
{
    if(this->topBound == this->downBound || this->rightBound == this->leftBound)
        return true;
    return false;
}

Vector2D FieldBound::getTopLeft()
{
    Vector2D v(leftBound, topBound);
    return v;
}

Vector2D FieldBound::getTopRight()
{
    Vector2D v(rightBound, topBound);
    return v;
}

Vector2D FieldBound::getDownLeft()
{
    Vector2D v(leftBound, downBound);
    return v;
}

Vector2D FieldBound::getDownRight()
{
    Vector2D v(rightBound, downBound);
    return v;

}
