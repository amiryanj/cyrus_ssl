#ifndef DYNAMICOBSTACLE_H
#define DYNAMICOBSTACLE_H

#include "obstacle.h"

class DynamicObstacle : public Obstacle
{
public:
    DynamicObstacle(ObstacleType type, b2Vec2 center, double radius, b2Vec2 velocity);

    b2Vec2 velocity;
};

#endif // DYNAMICOBSTACLE_H
