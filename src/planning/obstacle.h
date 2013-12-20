#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <Box2D/Collision/Shapes/b2Shape.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include "../tools/vector3d.h"
#include "../tools/vector2d.h"

class Obstacle
{

public:
    Obstacle(const Vector2D &center, double radius, double orien, bool isMoving = false);
    Obstacle(const Vector2D &center, double width, double height, double orien, bool isMoving = false);
    b2Shape* shape;

    Vector2D Center;
    double orien;

    bool moving;

};

#endif // OBSTACLE_H
