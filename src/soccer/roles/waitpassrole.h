#ifndef WAITFORPASSROLE_H
#define WAITFORPASSROLE_H

#include "sslrole.h"
#include "../definition/SSLRobot.h"
#include "../SSLSkill.h"
#include "../ai/SSLAnalyzer.h"
#include "../ai/SSLGame.h"
#include "../ai/SSLWorldModel.h"
#include "../sslsocermath.h"

class WaitPassRole : public SSLRole
{

public:
    WaitPassRole(SSLAgent* agent);

    void run();

    Vector3D getBestPosition() const;
    void setBestPosition(const Vector3D &value);

private:
    Vector3D m_bestPosition;
};

#endif // WAITFORPASSROLE_H
