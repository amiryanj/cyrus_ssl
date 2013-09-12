#ifndef SSLROBOT_H
#define SSLROBOT_H

#include <QVector3D>
#include "SSLRobotPhysic.h"
#include "general.h"
#include "SSLObject.h"

class SSLRobot : public SSLObject
{
public:
    SSLRobot();

    uint id;
    Color color;
    QString colorStr;

    bool isInField;

    QVector3D localSpeed() const;
    double orien_radian() const;

    SSLRobotPhysic physic;

};

#endif // SSLROBOT_H
