#ifndef _DEFENDER_H
#define _DEFENDER_H

#include "../sslrole.h"
#include "../sslskill.h"

class Defender : public SSLRole
{
public:

    static const double SMALLEST_TIME_TO_SHOOT = 1.0;

    Defender(int ind, int count);

    void run();

    int getDefenderCount() const;
    void setDefenderCount(int ind);

    int getDefenderIndex() const;
    void setDefenderIndex(int ind);

    Vector3D expectedPosition();

private :
    int m_defenderCount;
    int m_defenderIndex;
};

#endif // _DEFENDER_H
