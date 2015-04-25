#include "rectangularfieldbound.h"
#include "vector2d.h"
#include "randomsampling.h"
#include <cmath>

RectangularFieldBound::RectangularFieldBound()
{
    this->topBound  =  INFINITY;
    this->downBound = -INFINITY;
    this->rightBound=  INFINITY;
    this->leftBound = -INFINITY;
}

RectangularFieldBound::RectangularFieldBound(float left, float right, float down, float top)
{
    this->set(left, right, down, top);
}

Vector3D RectangularFieldBound::getUniformSample()
{
    float rx = uni_rand(this->getDownLeft().X(), this->getTopRight().X());
    float ry = uni_rand(this->getDownLeft().Y(), this->getTopRight().Y());
    float rt = uni_rand(-M_PI, M_PI);
    return Vector3D(rx, ry, rt);
}

void RectangularFieldBound::set(float left, float right, float down, float top)
{
    this->topBound = top;
    this->downBound = down;
    this->rightBound = right;
    this->leftBound = left;
}

void RectangularFieldBound::set(Vector2D downLeft, Vector2D topRight)
{
    this->leftBound = downLeft.X();
    this->downBound = downLeft.Y();
    this->rightBound = topRight.X();
    this->topBound = topRight.Y();
}

bool RectangularFieldBound::isEmpty()
{
    if(this->topBound == this->downBound || this->rightBound == this->leftBound)
        return true;
    return false;
}

Vector2D RectangularFieldBound::getTopLeft()
{
    Vector2D v(leftBound, topBound);
    return v;
}

Vector2D RectangularFieldBound::getTopRight()
{
    Vector2D v(rightBound, topBound);
    return v;
}

Vector2D RectangularFieldBound::getDownLeft()
{
    Vector2D v(leftBound, downBound);
    return v;
}

Vector2D RectangularFieldBound::getDownRight()
{
    Vector2D v(rightBound, downBound);
    return v;
}
