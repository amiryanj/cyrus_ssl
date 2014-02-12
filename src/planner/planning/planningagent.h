#ifndef PLANNINGROBOT_H
#define PLANNINGROBOT_H

#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include "station.h"
#include "control.h"

class PlanningAgent
{

public:
    PlanningAgent(b2Shape::Type type = b2Shape::e_circle);

    b2Shape *shape;
    void setRadius(double rad);

    Control velocity_limit;
    double max_accel;

//    double max_vel;
//    double max_rot; // radian
    double mass;

    PlanningAgent& operator=(const PlanningAgent& other);

private:

};

#endif // PLANNINGROBOT_H
