#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <Box2D/Collision/Shapes/b2Shape.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <tools/vector3d.h>
#include <tools/vector2d.h>
#include <vector>

class Obstacle
{

public:
    Obstacle(b2Vec2 center, double radius, double orien, bool isMoving = false);
    Obstacle(b2Vec2 center, double width, double height, double orien, bool isMoving = false);
    ~Obstacle();
    b2Transform transform;

    b2Shape* shape;


//    double orien;

    bool dynamic;

};

typedef std::vector<Obstacle*> ObstacleSet;

#endif // OBSTACLE_H
