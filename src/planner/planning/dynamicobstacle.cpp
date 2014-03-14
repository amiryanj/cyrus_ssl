#include "dynamicobstacle.h"

DynamicObstacle::DynamicObstacle(ObstacleType type, b2Vec2 center, double radius, b2Vec2 velocity) :
    Obstacle(type, center, radius, 0, true),    velocity(velocity)
{

}
