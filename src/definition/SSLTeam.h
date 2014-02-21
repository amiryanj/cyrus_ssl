#ifndef SSLTEAM_H
#define SSLTEAM_H

#include <vector>
#include <string>
#include "general.h"
#include "SSLRobotPhysic.h"

using namespace std;
using namespace SSL;

class SSLRobot;

class SSLTeam
{
public:
    //SSLTeam();
    SSLTeam(const Side side, const Color color, const SSLRobotPhysic &physic);
    SSLRobot *robot[MAX_ID_NUM];
    unsigned int numInFields() const;
    vector<SSLRobot*> inFields();
    vector<SSLRobot*> allRobots();

    Side side;
    Color color;
    std::string colorStr();

private:
//    vector<SSLRobot*> _in_fields;

};

#endif // SSLTEAM_H
