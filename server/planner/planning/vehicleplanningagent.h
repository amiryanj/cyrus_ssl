#ifndef _VEHICLEPLANNINGROBOT_H
#define _VEHICLEPLANNINGROBOT_H

#include "planningagent.h"
#include <Box2D/Collision/Shapes/b2PolygonShape.h>

class VehiclePlanningAgent : public PlanningAgent
{
public:
    VehiclePlanningAgent(double width, double length) {
        b2PolygonShape *poly_shape = new b2PolygonShape;
        poly_shape->SetAsBox(width/2, length/2);
        shape = poly_shape;
        shape->m_radius = fmax(width, length)/2.0;
    }

    Station &step(const Station &st, const Vector3D &global_control, float step_time);

private:

};

#endif // _VEHICLEPLANNINGROBOT_H
