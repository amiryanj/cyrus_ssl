#include "obstacle.h"

Obstacle::Obstacle(b2Vec2 center, double radius, double orien,  bool isMoving)
{
    shape = new b2CircleShape();
    b2CircleShape* circle = (b2CircleShape*) shape;
    circle->m_p.SetZero(); // = 0
    this->transform.Set(center, orien);

    shape->m_radius = radius;

//    this->orien = orien;

    this->dynamic = isMoving;
}

Obstacle::Obstacle(b2Vec2 center, double width, double height, double orien, bool isMoving)
{
    shape = new b2PolygonShape();
    shape->m_type = b2Shape::e_polygon;    

    ((b2PolygonShape*)shape)->SetAsBox(width, height); // , center, orien);
    this->transform.Set(center, orien);

//    this->orien = orien;

    this->dynamic = isMoving;
}

Obstacle::~Obstacle()
{
    if(this->shape)
        delete shape;
}
