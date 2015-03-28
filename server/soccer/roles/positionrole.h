#ifndef POSITIONROLE_H
#define POSITIONROLE_H

#include "../sslrole.h"
#include "../sslskill.h"

class PositionRole : public SSLRole
{
public:
    PositionRole();

    Vector3D getPosition() const;
    void setPosition(const Vector3D &value);

    Vector3D getTolerance() const;
    void setTolerance(const Vector3D &value);

    void run();

    Vector3D expectedPosition();

private:
    Vector3D m_position;
    Vector3D m_tolerance;
};

#endif // POSITIONROLE_H
