#ifndef _SSL_PLANNINGROBOT_H
#define _SSL_PLANNINGROBOT_H

#include "planningagent.h"
#include "general.h"
#include <Box2D/Collision/Shapes/b2CircleShape.h>

class SSLPlanningAgent : public PlanningAgent
{
public:
    SSLPlanningAgent() {
        shape = new b2CircleShape;
        shape->m_radius = ROBOT_RADIUS;
    }

    Station &step(const Station &st, const Vector3D &global_control, float step_time);

private:

};

#endif // _SSL_PLANNINGROBOT_H
