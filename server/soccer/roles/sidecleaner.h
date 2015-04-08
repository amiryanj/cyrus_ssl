#ifndef _SIDECLEANER_H
#define _SIDECLEANER_H

#include "../sslrole.h"

class SideCleaner : public SSLRole
{

public:
    enum CleanSide{eCleanTopField, eCleanDownField} m_side;
    SideCleaner(CleanSide _side);

    void run();

    Vector3D expectedPosition();

private:


};

#endif // _GOALKEEPER_H
