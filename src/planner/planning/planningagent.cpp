#include "planningagent.h"

PlanningAgent::PlanningAgent(b2Shape::Type type)
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
}

void PlanningAgent::setRadius(double rad)
{
    shape->m_radius = rad;
}

PlanningAgent &PlanningAgent::operator =(const PlanningAgent &other)
{
    this->shape->m_radius = other.shape->m_radius;
//    this->velocity_limit = other.velocity_limit;
    this->mass = other.mass;
}
