#ifndef _RECTANGULARFIELDBOUND_H
#define _RECTANGULARFIELDBOUND_H

#include "fieldbound.h"

class Vector2D;

class RectangularFieldBound : public FieldBound
{
public:
    RectangularFieldBound();
    RectangularFieldBound(float left, float right, float down, float top);

    Vector3D getUniformSample();
    bool isEmpty();

    void set(float left, float right, float down, float top);
    void set(Vector2D downLeft, Vector2D topRight);

    Vector2D getTopLeft();
    Vector2D getTopRight();
    Vector2D getDownLeft();
    Vector2D getDownRight();

protected:
    float topBound;
    float downBound;
    float rightBound;
    float leftBound;
};



#endif // FIELDBOUND_H
