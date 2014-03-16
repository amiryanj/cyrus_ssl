#ifndef DEFENCEROLE_H
#define DEFENCEROLE_H

#include "sslrole.h"
#include "../sslsocermath.h"
#include "../SSLSkill.h"
#include "../ai/SSLAnalyzer.h"
#include "../ai/SSLGame.h"
#include "../ai/SSLWorldModel.h"

class DefenderRole : public SSLRole
{
public:

    static const double SMALLEST_TIME_TO_SHOOT = 1.0;

    DefenderRole(SSLAgent* agent);

    void run();

    int getDefenderCount() const;
    void setDefenderCount(int ind);

    int getDefenderIndex() const;
    void setDefenderIndex(int ind);

private :
    int m_defenderCount;
    int m_defenderIndex;
};

#endif // DEFENCEROLE_H
