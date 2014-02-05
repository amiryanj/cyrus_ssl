#include "planneragent.h"
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>

using namespace Planner;

PlannerAgent::PlannerAgent(b2Shape::Type type)
{
    switch(type)
    {
    case b2Shape::e_circle:
        shape = new b2CircleShape();
        break;

    case b2Shape::e_polygon :
        shape = new b2PolygonShape();
        break;
    }

//    this->init_position = init_pos;
}

PlannerAgent &PlannerAgent::operator =(const PlannerAgent &other)
{
    this->shape->m_radius = other.shape->m_radius;
    this->max_vel =  other.max_vel;
    this->max_rot = other.max_rot;
    this->mass = other.mass;
}
