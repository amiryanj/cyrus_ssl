#include "obstacle.h"

Obstacle::Obstacle(const Vector2D &center, double radius, double orien,  bool isMoving)
{
    shape = new b2CircleShape();
    Center = center;
    shape->m_radius = radius;

    this->orien = orien;

    this->moving = isMoving;

}

Obstacle::Obstacle(const Vector2D &center, double width, double height, double orien, bool isMoving)
{
    shape = new b2PolygonShape();
    shape->m_type = b2Shape::e_polygon;
    Center = center;

    ((b2PolygonShape*)shape)->SetAsBox(width, height);

    this->orien = orien;

    this->moving = isMoving;
}
