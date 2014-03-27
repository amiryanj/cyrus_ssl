#ifndef _WAITPASS_H
#define _WAITPASS_H

#include "sslrole.h"
#include "../SSLSkill.h"

class WaitPass : public SSLRole
{

public:
    WaitPass();

    void run();

    Vector3D getBestPosition() const;
    void setBestPosition(const Vector3D &value);

    Vector2D expectedPosition();

private:
    Vector3D m_bestPosition;
};

#endif // _WAITPASS_H
