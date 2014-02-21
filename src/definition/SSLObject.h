#ifndef SSLOBJECT_H
#define SSLOBJECT_H

#include "../tools/vector3d.h"
#include "../tools/vector2d.h"

enum SSL_OBJECT_TYPE {BALL_OBJECT, ROBOT_OBJECT};

template <class VectorType>
class SSLObject
{
public:
    SSLObject() {}

    VectorType Position() const    {
        return this->_position;
    }

    VectorType Speed() const    {
        return this->_speed;
    }

    void setPosition(const VectorType &position_)   {
        this->_position = position_;
    }

    void setSpeed(const VectorType &speed_)     {
        this->_speed = speed_;
    }
        ;
    double radius;

protected:
    VectorType _position;
    VectorType _speed;

    SSL_OBJECT_TYPE type;
    double mass;

};

#endif // SSLOBJECT_H
