#ifndef ANALYZER_H
#define ANALYZER_H

#include "../general.h"
#include "../tools/SSLListener.h"
#include <vector>
#include <map>

class SSLGame;
class SSLWorldModel;
class SSLTeam;
class SSLRobot;
class SSLBall;

using namespace SSL;

// Singleton Class
class SSLAnalyzer : SSLListener
{
private:
    SSLAnalyzer();  // default constructor
    static SSLAnalyzer *analyzer;

    double access_time[2][MAX_ID_NUM];
    Vector2D access_intercept[2][MAX_ID_NUM];
    SSLWorldModel *world();
    
    void updateAllAccessTimes();

    double timeToAccessBall(const SSLRobot &robot, const SSLBall &ball, double precison = 0.001);

public:
    // return class static object
    static SSLAnalyzer *getInstance();

    // main function which is called by main thread inherited from SSL-Listener
    void check();

    double minAccessTime(std::vector<SSLRobot*> robots, SSLBall* ball);

    SSLRobot* nearestPlayer(std::vector<SSLRobot*> robots);

    bool canKick(const SSLRobot& robot, SSLBall *ball);
    bool canNearestPlayerShoot(SSLTeam* team, SSLBall *ball);

    double possessionRatio(std::vector<SSLRobot*> robots);

    std::vector<double> openAnglesToGoal(const Vector2D &point, Side targetGoalSide, std::vector<SSLRobot*> defenders);
//    std::vector<double> openAnglesToGoal(const Vector2D &point, Side targetGoalSide, std::vector<SSLRobot*> defenders)
    double totalOpenAngle(const Vector2D &point, Side targetGoalSide, std::vector<SSLRobot*> defenders);
    
};

#endif // ANALYZER_H
