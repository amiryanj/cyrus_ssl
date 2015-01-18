#ifndef _BLOCKER_H
#define _BLOCKER_H

#include "sslrole.h"
#include "../../definition/SSLRobot.h"
#include "../SSLSkill.h"

class Blocker : public SSLRole
{
public:
    Blocker(int index_);

    void run();
    Vector3D expectedPosition();

    int m_index;

private:

};

#endif // BLOCKER_H
