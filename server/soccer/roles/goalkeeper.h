#ifndef _GOALKEEPER_H
#define _GOALKEEPER_H

#include "../sslrole.h"

class GoalKeeper : public SSLRole
{
public:
    GoalKeeper();

    void run();

    Vector3D expectedPosition();

private:


};

#endif // _GOALKEEPER_H
