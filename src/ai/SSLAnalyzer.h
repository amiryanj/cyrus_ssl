#ifndef _ANALYZER_H
#define _ANALYZER_H

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
using namespace std;

#define analyzer SSLAnalyzer::getInstance()

// Singleton Class
class SSLAnalyzer : SSLListener
{
private:
    SSLAnalyzer();  // default constructor
    static SSLAnalyzer *analyzer_instance;

    void updateDistances();
    std::pair<float, Vector2D> whenWhereCanRobotCatchTheBall_imp1(const SSLRobot* robot);
    std::pair<float, float> blockedAngleByARobot(const Vector2D & vec, const SSLRobot* robot);
    float positiveSideAngleInNegativeSide(float angle) const;
    float negativeSideAngleInPositiveSide(float angle) const;

public:
    static SSLAnalyzer *getInstance();
    void check();

//    //LEVEL 0 : BASICS -------------------------------------------------------------------------

    double distanceFromBall(const Vector2D & point);
    double distanceFromBall(const SSLRobot * robot);
    double distanceFromRobotToPoint(const Vector2D & point,const SSLRobot * robot);
    double distanceFromRobotToRobot(const SSLRobot * robot1,const SSLRobot * robot2);

//    //LEVEL 1  --------------------------------------------------------------------------------

    SSLRobot* whichRobotCanKick(); // Null : none
    bool canKick(SSLRobot* robot);

    vector<pair<float,pair<Vector2D, SSLRobot *> > > nearestRobotToBall();
    vector<pair<float,pair<Vector2D, SSLRobot *> > > nearestRobotToBall(const SSL::Color & teamColor);
    vector<pair<float,pair<Vector2D, SSLRobot *> > > nearestRobotToBall(const vector<SSLRobot *> & robots);

    vector<SSLRobot*> nearestRobotToPoint(const Vector2D & point);
    vector<SSLRobot*> nearestRobotToPoint(const SSL::Color & teamColor,const Vector2D & point);
    vector<SSLRobot*> nearestRobotToPoint(const vector<SSLRobot*> & robots,const Vector2D & point);


    vector<SSLRobot*> nearestRobotToRobot(const SSLRobot * robot);
    vector<SSLRobot*> nearestRobotToRobot(const SSL::Color teamColor,const SSLRobot * robot);
    vector<SSLRobot*> nearestRobotToRobot(const vector<SSLRobot*> & robots,const SSLRobot * robot);

//   //LEVEL 2 : ROBOT & ROBOT ------------------------------------------------------------------
    std::vector<SSLRobot *> nearestRobotsToBlockPointOutOfOurPenaltyArea(const Vector2D targetPoint);
    std::vector<SSLRobot *> nearestRobotsToBlockPoint(const Vector2D targetPoint);
    std::vector<SSLRobot *> nearestRobotsToMarkRobot(const SSLRobot * robot); // nazdiktarin robot be robot

// LEVEL 3 : PREDICTION ---------------------------------------------------------------------

    std::pair<float, Vector2D> whenWhereCanRobotCatchTheBall(const SSLRobot* robot);
    std::vector<SSLRobot *> opponentBlockerFromPoint(const Vector2D targetPoint);
    std::vector<pair<float,float> > openAngleToGoal(const Vector2D targetPoint);

// temp fuction ---------------------------------------------------------------------
    int nearestRobotToBallForVisualizer(Color);

// Referee State Analyze:
    bool isOurKickOffPosition();
    bool isOpponentKickOffPosition();
    bool isOurKickOffKick();
    bool isOpponentKickOffKick();

    bool isOurPenaltyPosition();
    bool isOpponentPenaltyPosition();
    bool isOurPenaltyKick();
    bool isOpponentPenaltyKick();

    bool isOurDirectKick();
    bool isOpponentDirectKick();
    bool isOurIndirectKick();
    bool isOpponentIndirectKick();

    bool isGameRunning();
    bool isPointWithinOurPenaltyArea(const Vector2D& point);
    bool isPointInOurSide(const Vector2D& point);

private:
    bool m_game_running;

};

#endif // _ANALYZER_H
