#ifndef _WALLSTANDER_H
#define _WALLSTANDER_H

#include "sslrole.h"

#define DEFAULT_WALL_RADIUS     500

class WallStander : public SSLRole
{

public:
    WallStander(float wallRadius = DEFAULT_WALL_RADIUS, short index = 1, short count = 1);

    void run();
    float m_wallRadius;
    short m_standerIndex;
    short m_standerCount;

    Vector2D expectedPosition();

private:

};

#endif // _WALLSTANDER_H
