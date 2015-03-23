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
    default:
        shape = new b2CircleShape();
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
    this->velocity_limit = other.velocity_limit;
    this->max_accel = other.max_accel;
    this->mass = other.mass;
    return *this;
}

float PlanningAgent::radius()
{
    return this->shape->m_radius;
}
