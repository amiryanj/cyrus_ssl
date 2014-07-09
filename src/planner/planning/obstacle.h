#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <Box2D/Collision/Shapes/b2Shape.h>
#include <Box2D/Common/b2Math.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include "math/vector3d.h"
#include "math/vector2d.h"
#include <vector>

class Obstacle
{
public:
    enum ObstacleType{ Ball, Robot, Field};

    Obstacle(ObstacleType type, b2Vec2 center, double radius, double orien);
    Obstacle(ObstacleType type, b2Vec2 center, double width, double height, double orien);
    ~Obstacle();

    ObstacleType m_ObstacleType;
    b2Transform m_transform;
    void getOut();

    b2Shape* shape;

    bool dynamic;

};

typedef std::vector<Obstacle*> ObstacleSet;

#endif // OBSTACLE_H
