#ifndef PLANNERBOUND_H
#define PLANNERBOUND_H

#include "../tools/vector2d.h"
#include "climits"
#include "math.h"

namespace Planner{
class PlannerBound
{
public:
    PlannerBound();
    PlannerBound(double left, double down, double right, double top);
    void set(double left, double down, double right, double top);
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
}

#endif // PLANNERBOUND_H
