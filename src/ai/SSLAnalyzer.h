#ifndef ANALYZER_H
#define ANALYZER_H

#include "SSLWorldModel.h"
#include "general.h"
#include "tools/SSLListener.h"

class SSLGame;

class SSLAnalyzer : SSLListener
{

private:
    SSLAnalyzer();
    static SSLAnalyzer *analyzer;

    SSLWorldModel *world;
    double access_time[2][MAX_ID_NUM];
    Vector2D access_intercept[2][MAX_ID_NUM];
    
public:
    static SSLAnalyzer *getInstance();

    void check();

    void updateAllAccessTimes();
    double calcAccessTime(SSLRobot* robot, SSLBall* ball);
    SSLRobot* nearestPlayer(SSLTeam* team);
    double possessionRatio();
    double minAccessTime(SSLTeam* team);
    bool canNearestPlayerShoot(SSLTeam* team, SSLBall *ball);
    double angleForRotate(SSLRobot* robot, Vector2D interceptPoint);
    //double angleToGoal(teamSide GoalSide, const QPoint point);
    std::list<double> openAnglesToGoal(const Vector2D &point, Side targetGoalSide, std::list<SSLRobot*> defenders);
    double totalOpenAngle(const Vector2D &point, Side targetGoalSide, std::list<SSLRobot*> defenders);
    
};

#endif // ANALYZER_H
