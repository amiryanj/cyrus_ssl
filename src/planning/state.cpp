#include "state.h"
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <iostream>

using namespace Planner;

State::State()
{
    position = Vector2D(0, 0);
    heading = 0;
    curvature = 0;
    velocity = 0;
}

//State::State(State &other)
//{
//    this->position = other.position;
//    this->heading = other.heading;
//    this->velocity = other.velocity;
//}

State::State(Vector2D pos, double head, double vel)
{
    this->position = pos;
    this->heading = head;
    this->velocity = vel;
}

bool State::isNull()
{
    if(position==Vector2D(0,0) && heading == 0 && velocity == 0)
        return true;
    return false;
}

State State::operator -(State other)
{
    State temp;
    temp.position = this->position - other.position;
    temp.heading = this->heading; // - other.heading;
    temp.velocity = this->velocity;
    return temp;
}

State State::operator +(State other)
{
    State temp;
    temp.position = this->position + other.position;
    temp.heading = this->heading;
    temp.velocity = this->velocity;
    return temp;
}

State &State::operator *=(double mul)
{
    this->position *= mul;
    return (*this);
}

double State::distTo(const State &other)
{
    return(this->position - other.position).lenght();
}

double State::distToB(const State &other)
{
    b2Transform transform;
    double cir_radius = this->velocity * 5;
    b2CircleShape carBannedCircle;
    carBannedCircle.m_radius = cir_radius;

    if(other.position.X() < this->position.X())
        return INFINITY;

    b2Vec2 cir_position = b2Vec2(this->position.X() + cir_radius*sin(this->heading* M_PI / 180.0),
                                 this->position.Y() - cir_radius*cos(this->heading* M_PI / 180.0));
    transform.Set(cir_position, 0);
    if(carBannedCircle.TestPoint(transform, b2Vec2(other.position.X(), other.position.Y())))
        return INFINITY;

    cir_position = b2Vec2(this->position.X() - cir_radius*sin(this->heading* M_PI / 180.0),
                                 this->position.Y() + cir_radius*cos(this->heading* M_PI / 180.0));
    transform.Set(cir_position, 0);
    if(carBannedCircle.TestPoint(transform, b2Vec2(other.position.X(), other.position.Y())))
        return INFINITY;
    double dist = (this->position - other.position).lenght();
    return dist; // euclidean distance between 2 state
}

bool State::operator ==(State other)
{
    if(position==other.position && heading == other.heading && velocity == other.velocity)
        return true;
    return false;
}

State &State::operator =(State other)
{
    this->position = other.position;
    this->heading = other.heading;
    this->velocity = other.velocity;
    return (*this);
}
