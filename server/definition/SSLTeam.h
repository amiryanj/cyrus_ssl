#ifndef SSLTEAM_H
#define SSLTEAM_H

#include <vector>
#include <string>
#include "../../common/sslnamespace.h"
#include "../../common/general.h"

using namespace std;
using namespace SSL;

class SSLRobot;
class SSLRobotPhysics;

class SSLTeam
{
public:
    //SSLTeam();
    SSLTeam(const Color color, const SSLRobotPhysics &physic);
    SSLRobot *robot[MAX_ID_NUM];

    unsigned int numInFieldRobots() const;

    vector<SSLRobot*> getAllRobots();
    vector<SSLRobot*> getInFieldRobots();
    vector<SSLRobot*> getInFieldRobotsExcept(int id);
    vector<SSLRobot*> getInFieldRobotsExcept(SSLRobot* robot);

    Color color;
    std::string colorStr();

private:
//    vector<SSLRobot*> _in_fields;

};

#endif // SSLTEAM_H
