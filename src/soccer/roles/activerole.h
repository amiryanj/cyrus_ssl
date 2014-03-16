#ifndef ACTIVEROLE_H
#define ACTIVEROLE_H

#include "sslrole.h"
#include "../SSLSkill.h"
#include "../ai/SSLAnalyzer.h"
#include "../ai/SSLGame.h"
#include "../ai/SSLWorldModel.h"
#include "../sslsocermath.h"

class ActiveRole : public SSLRole
{
public:
    ActiveRole(SSLAgent* agent);

    void run();
};

#endif // ACTIVEROLE_H
