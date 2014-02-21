#ifndef FIELDBOUND_H
#define FIELDBOUND_H

#include "../../tools/vector2d.h"
#include <cmath>

class FieldBound
{
public:
    FieldBound();
    FieldBound(double left, double right, double down, double top);
    void set(double left, double right, double down, double top);
    void set(Vector2D downLeft, Vector2D topRight);

    bool isEmpty();

    Vector2D getTopLeft();
    Vector2D getTopRight();
    Vector2D getDownLeft();
    Vector2D getDownRight();

    double topBound;
    double downBound;
    double rightBound;
    double leftBound;
};



#endif // FIELDBOUND_H
