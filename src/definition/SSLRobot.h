#ifndef SSLROBOT_H
#define SSLROBOT_H

#include "SSLRobotPhysic.h"
#include "general.h"
#include "SSLObject.h"

#include "SSLTeam.h" //SSLTeam;

class SSLRobot : public SSLObject<Vector3D>
{
public:
    SSLRobot(SSLTeam* team = 0);
    SSLTeam* team;

    unsigned int id;
    Color color;
    std::string colorStr();

    bool isInField;

    Vector3D localSpeed() const;
    double orien() const;

    SSLRobotPhysic physic;

};

#endif // SSLROBOT_H
