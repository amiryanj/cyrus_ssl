#ifndef _BLOCKER_H
#define _BLOCKER_H

#include "sslrole.h"
#include "../../definition/SSLRobot.h"
#include "../SSLSkill.h"

class Blocker : public SSLRole
{
public:
    Blocker();

    SSLRobot *getBlockedRobot() const;
    void setBlockedRobot(SSLRobot *value);

    void run();
    Vector3D expectedPosition();

private:
    SSLRobot* m_blockedRobot;
};

#endif // BLOCKER_H
