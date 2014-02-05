#ifndef PLANNERAGENT_H
#define PLANNERAGENT_H

#include <Box2D/Collision/Shapes/b2Shape.h>

namespace Planner{
class PlannerAgent
{

public:
    PlannerAgent(b2Shape::Type type = b2Shape::e_circle);

    b2Shape *shape;

    double max_vel;
    double max_rot; // radian
    double mass;

    PlannerAgent& operator=(const PlannerAgent& other);

//private:
};
}


#endif // PLANNERAGENT_H
