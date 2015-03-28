#ifndef SSLROLE_H
#define SSLROLE_H

#include "../../ai/SSLWorldModel.h"
#include "../../ai/SSLGame.h"
#include "../../ai/SSLAnalyzer.h"

#include "../../definition/SSLBall.h"
#include "../SSLSkill.h"
#include "../sslgamepositions.h"

class SSLAgent;

class SSLRole
{
public:
    enum Type{ e_Active, e_Blocker, e_Defender, e_GoalKeeper, e_OpponentMarker,
               e_PlayStarter, e_Position, e_WaitPass, e_WaitRebound, e_WallStander };

    SSLRole();
    void setAgent(SSLAgent* agent);

    virtual void run() = 0;
    virtual Vector3D expectedPosition() = 0;
    bool Halt();

    SSLAgent* m_agent;
    Type m_type;
    short m_hardness;

protected:
    enum ActiveRoleState { e_FarFromBall, e_NearBall, e_CanKick} m_state;


private:

};

#endif // SSLROLE_H
