#ifndef BLOCKROBOTROLE_H
#define BLOCKROBOTROLE_H

#include "sslrole.h"
#include "../definition/SSLRobot.h"
#include "../SSLSkill.h"
#include "../ai/SSLAnalyzer.h"
#include "../ai/SSLGame.h"
#include "../ai/SSLWorldModel.h"
#include "../sslsocermath.h"

class BlockRole : public SSLRole
{
public:
    BlockRole(SSLAgent* agent);

    SSLRobot *getBlockedRobot() const;
    void setBlockedRobot(SSLRobot *value);

    void run();

private:
    SSLRobot* m_blockedRobot;
};

#endif // BLOCKROBOTROLE_H
