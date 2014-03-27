#ifndef SSLOBJECT_H
#define SSLOBJECT_H

#include "../tools/vector3d.h"
#include "../tools/vector2d.h"

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

    void setPosition(const VectorType &position_)   {
        m_position = position_;
    }

    void setSpeed(const VectorType &speed_)     {
        m_speed = speed_;
    }

    double m_radius;

protected:
    VectorType m_position;
    VectorType m_speed;

    SSL_OBJECT_TYPE m_type;
    double m_mass;

};

#endif // SSLOBJECT_H
