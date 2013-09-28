#ifndef SSLROBOT_H
#define SSLROBOT_H

#include "SSLRobotPhysic.h"
#include "general.h"
#include "SSLObject.h"

class SSLRobot : public SSLObject
{
public:
    SSLRobot();

    unsigned int id;
    Color color;
    string colorStr;

    bool isInField;

    Vector3D localSpeed() const;
    double orien() const;

    SSLRobotPhysic physic;

};

#endif // SSLROBOT_H
