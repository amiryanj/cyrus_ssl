#ifndef ANALYZER_H
#define ANALYZER_H

#include "../general.h"
#include "../tools/SSLListener.h"
#include "robottoballdistance.h"
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

    SSLWorldModel *world();
    
    void updateDistances();

    RobotDistTo* distToBall[2][MAX_ID_NUM];

public:
    // return class static object
    static SSLAnalyzer *getInstance();

    // main function which is called by main thread inherited from SSL-Listener
    void check();

    double getTimeToBall(const SSLRobot& robot);

    const SSLRobot* nearestPlayerToBall() const; // among all robots
    const SSLRobot* nearestPlayerToBall(SSL::Color team_color);
    const SSLRobot* nearestPlayerToBall(std::vector<SSLRobot*> robots);

    const SSLRobot* nearestPlayerToPoint(Vector2D point); // among all robots
    const SSLRobot* nearestPlayerToPoint(Vector2D point, SSL::Color team_color);
    const SSLRobot* nearestPlayerToPoint(const Vector2D &point, std::vector<SSLRobot*> robots);

    bool canKick(const SSLRobot *robot);
    SSLRobot* inKickPosition(SSL::Color team_color);

    double possessionRatio(SSL::Color team_A, SSL::Color team_B);

    std::vector<double> openAnglesToGoal(const Vector2D &point, Side targetGoalSide, std::vector<SSLRobot*> defenders);
//    std::vector<double> openAnglesToGoal(const Vector2D &point, Side targetGoalSide, std::vector<SSLRobot*> defenders)
    double totalOpenAngle(const Vector2D &point, Side targetGoalSide, std::vector<SSLRobot*> defenders);
    
};

#endif // ANALYZER_H
