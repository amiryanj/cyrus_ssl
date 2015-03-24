#include "obstacle.h"

Obstacle::Obstacle(ObstacleType type, b2Vec2 center, double radius)
{
    shape = new b2CircleShape();
    b2CircleShape* circle = (b2CircleShape*) shape;
    circle->m_p.SetZero(); // = 0
    this->m_transform.Set(center, 0);

    shape->m_radius = radius;

    this->m_ObstacleType = type;
    repulseStrenght = 1.0;

//    this->dynamic = isMoving;
}

Obstacle::Obstacle(ObstacleType type, b2Vec2 center, double width, double height, double orien)
{
    shape = new b2PolygonShape();
    shape->m_type = b2Shape::e_polygon;    

    ((b2PolygonShape*)shape)->SetAsBox(width/2, height/2); // , center, orien);
    this->m_transform.Set(center, orien);

    this->m_ObstacleType = type;

//    this->dynamic = isMoving;
}

Obstacle::~Obstacle()
{
    if(this->shape)
        delete shape;
}

void Obstacle::getOut()
{
    this->m_transform.Set(b2Vec2(INFINITY, INFINITY), 0);
}
