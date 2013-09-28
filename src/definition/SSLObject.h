#ifndef SSLOBJECT_H
#define SSLOBJECT_H

#include "tools/vector3d.h"
#include "tools/vector2d.h"

enum SSL_OBJECT_TYPE {BALL_OBJECT, ROBOT_OBJECT};

class SSLObject
{
public:
    SSLObject();
    Vector3D Position() const;
    Vector3D Speed() const;
    void setPosition(const Vector3D &position_);
    void setSpeed(const Vector3D &speed_);

protected:
    Vector3D position_;
    Vector3D speed_;

    SSL_OBJECT_TYPE type;
    double radius;
    double mass;

};

#endif // SSLOBJECT_H
