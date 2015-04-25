#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <Box2D/Collision/Shapes/b2Shape.h>
#include <vector>
#include <string>

#include "../../../shared/utility/vector2d.h"

class Obstacle
{
public:
    Obstacle(Vector2D center, float radius, const char* details_ = 0);
    Obstacle(Vector2D center, float width, float height, float orien = 0, const char *details_ = 0);
    ~Obstacle() {
        if(this->shape)
            delete shape;
        shape = NULL;
    }

    b2Shape* shape;

    void setRadius(float radius_) {
        shape->m_radius = radius_;
    }

    b2Transform transform;
    b2Transform predictedTransform(float time_step_sec) const;

    float repulseStrenght;
    Vector2D speed;

    std::string detail_text;
};

typedef std::vector<Obstacle*> ObstacleSet;

#endif // OBSTACLE_H
