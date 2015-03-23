#ifndef PLANNINGROBOT_H
#define PLANNINGROBOT_H

#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include "station.h"

class PlanningAgent
{

public:
    PlanningAgent(b2Shape::Type type = b2Shape::e_circle);

    b2Shape *shape;

    Vector3D velocity_limit;
    double max_accel;

//    double max_vel;
    double maxRotationRad; // radian
    double mass;

    PlanningAgent& operator=(const PlanningAgent& other);

    void setRadius(double rad);
    float radius();

private:

};

#endif // PLANNINGROBOT_H
