#ifndef _DEFENDER_H
#define _DEFENDER_H

#include "sslrole.h"
#include "../SSLSkill.h"

class Defender : public SSLRole
{
public:

    static const double SMALLEST_TIME_TO_SHOOT = 1.0;

    Defender();

    void run();

    int getDefenderCount() const;
    void setDefenderCount(int ind);

    int getDefenderIndex() const;
    void setDefenderIndex(int ind);

    Vector2D expectedPosition();

private :
    int m_defenderCount;
    int m_defenderIndex;
};

#endif // _DEFENDER_H
