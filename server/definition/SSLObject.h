#ifndef SSLOBJECT_H
#define SSLOBJECT_H

#include "../../shared/utility/vector3d.h"
#include "../../shared/utility/vector2d.h"

enum SSL_OBJECT_TYPE {e_BALL_OBJECT, e_ROBOT_OBJECT};

template <class VectorType>
class SSLObject
{
public:
    SSLObject() {}

    VectorType Position() const    {
        return m_position;
    }

    VectorType Speed() const    {
        return m_speed;
    }

    VectorType Acceleration() const {
        return m_acceleration;
    }

    void setPosition(const VectorType &position_)   {
        m_position = position_;
    }

    void setSpeed(const VectorType &speed_)     {
        m_speed = speed_;
    }

    void setAcceleration(const VectorType &acceleration_) {
        m_acceleration = acceleration_;
    }

    float m_radius;

protected:
    VectorType m_position;
    VectorType m_speed;
    VectorType m_acceleration;

    double m_mass;

    SSL_OBJECT_TYPE m_type; // unused parameter

};

#endif // SSLOBJECT_H
