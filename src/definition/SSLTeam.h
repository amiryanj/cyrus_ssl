#ifndef SSLTEAM_H
#define SSLTEAM_H

#include <vector>
#include <string>
#include "SSLRobot.h"
#include "general.h"
#include "SSLRobotPhysic.h"

using namespace std;

class SSLTeam
{
public:
    //SSLTeam();
    SSLTeam(const Side side, const Color color, const SSLRobotPhysic &physic);
    SSLRobot *robot[MAX_ID_NUM];
    vector<SSLRobot*> inFieldRobots();
    unsigned int numInFieldRobots();

    Color color;
    string colorStr;

    Side side;

};

#endif // SSLTEAM_H
