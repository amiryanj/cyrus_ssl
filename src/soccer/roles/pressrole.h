#ifndef PRESSROBOTROLE_H
#define PRESSROBOTROLE_H

#include "sslrole.h"
#include "../definition/SSLRobot.h"
#include "../SSLSkill.h"
#include "../ai/SSLAnalyzer.h"
#include "../ai/SSLGame.h"
#include "../ai/SSLWorldModel.h"
#include "../sslsocermath.h"

class PressRole : public SSLRole
{
    static const double SMALLEST_TIME_TO_SHOOT = 1.0;

public:

    PressRole(SSLAgent* agent);

    SSLRobot *getBlockingRobot() const;
    void setBlockingRobot(SSLRobot *value);

    void run();

private:
    SSLRobot* m_blockingRobot; // The Robot who should be blocked
};

#endif // PRESSROBOTROLE_H
