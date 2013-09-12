#ifndef SSLTEAM_H
#define SSLTEAM_H

#include <QList>
#include <QString>
#include "SSLRobot.h"
#include "general.h"
#include "SSLRobotPhysic.h"

class SSLTeam
{
public:
    //SSLTeam();
    SSLTeam(Side side, Color color, SSLRobotPhysic physic);
    SSLRobot *robot[MAX_ID_NUM];
    QList<SSLRobot*> inFieldRobots();
    uint numInFieldRobots();

    Color color;
    QString colorStr;

    Side side;

};

#endif // SSLTEAM_H
