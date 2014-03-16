#ifndef POSITIONROLE_H
#define POSITIONROLE_H

#include "sslrole.h"
#include "../definition/SSLRobot.h"
#include "../SSLSkill.h"
#include "../sslsocermath.h"

class PositionRole : public SSLRole
{
public:
    PositionRole(SSLAgent* agent);

    float getFacing() const;
    void setFacing(float value);

    Vector2D getPosition() const;
    void setPosition(const Vector2D &value);

    void run();

private:
    Vector2D position;
    float facing;
};

#endif // POSITIONROLE_H
