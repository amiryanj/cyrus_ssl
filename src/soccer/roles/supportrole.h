#ifndef SUPPORTROLE_H
#define SUPPORTROLE_H

#include "sslrole.h"
#include "../definition/SSLRobot.h"
#include "../SSLSkill.h"
#include "../ai/SSLAnalyzer.h"
#include "../ai/SSLGame.h"
#include "../ai/SSLWorldModel.h"
#include "../sslsocermath.h"

class SupportRole : public SSLRole
{
public:
    SupportRole(SSLAgent* agent);

    void run();

};

#endif // SUPPORTROLE_H
