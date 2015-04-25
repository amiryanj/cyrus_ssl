#ifndef _PLANNINGROBOT_H
#define _PLANNINGROBOT_H

#include <Box2D/Collision/Shapes/b2Shape.h>
class Vector3D;
class Station;


class PlanningAgent
{

public:
    PlanningAgent() {}

    float radius() {
        return shape->m_radius;
    }

    b2Shape *shape;
    float mass;

    virtual Station &step(const Station &st, const Vector3D &global_control, float step_time_sec) = 0;

private:

};

#endif // PLANNINGROBOT_H
