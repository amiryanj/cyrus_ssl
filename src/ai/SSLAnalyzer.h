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
using namespace std;

// Singleton Class
class SSLAnalyzer : SSLListener
{
private:
    SSLAnalyzer();  // default constructor
    static SSLAnalyzer *analyzer;

    SSLWorldModel *world();
    SSLGame* game();
    
    void updateDistances();

public:
//    // return class static object
    static SSLAnalyzer *getInstance();

//    // main function which is called by main thread inherited from SSL-Listener
    void check();
    // TODO : initialize , and clear all caches

//    double getTimeToBall(const SSLRobot& robot);

//    const SSLRobot* nearestPlayerToBall() const; // among all robots
//    const SSLRobot* nearestPlayerToBall(SSL::Color team_color);
//    const SSLRobot* nearestPlayerToBall(std::vector<SSLRobot*> robots);

//    const SSLRobot* nearestPlayerToPoint(Vector2D point); // among all robots
//    const SSLRobot* nearestPlayerToPoint(Vector2D point, SSL::Color team_color);
//    const SSLRobot* nearestPlayerToPoint(const Vector2D &point, std::vector<SSLRobot*> robots);

//    bool canKick(std::vector<SSLRobot*> robots);

//    bool canRivalMakeAGoal(std::vector<SSLRobot*> robots); // Probability that competitor make a goal
//    bool havingBall(std::vector<SSLRobot*> robots); //is the ball in our Authority?
//    const SSLRobot* robotHaveBall(std::vector<SSLRobot*> robots); //which robot have the ball
//    const SSLRobot* nearestPlayerToBlock(std::vector<SSLRobot*> robots); //show nearest of our player that can block the ball



//    double possessionRatio(SSL::Color team_A, SSL::Color team_B);

//    std::vector<double> openAnglesToGoal(const Vector2D &point, Side targetGoalSide, std::vector<SSLRobot*> defenders);
////    std::vector<double> openAnglesToGoal(const Vector2D &point, Side targetGoalSide, std::vector<SSLRobot*> defenders)
//    double totalOpenAngle(const Vector2D &point, Side targetGoalSide, std::vector<SSLRobot*> defenders);
    
//LEVEL 0 : BASICS -------------------------------------------------------------------------
    int distanceFromBall(Vector2D point);
    int distanceFromBall(SSLRobot * robot);
    int distanceFromRobotToPoint(Vector2D point,SSLRobot * robot);
    int distanceFromRobotToRobot(SSLRobot * robot1,SSLRobot * robot2);
    bool mySort(pair<SSLRobot*, int>i, pair<SSLRobot*, int>j);

// LEVEL 1  --------------------------------------------------------------------------------
//    SSLRobot* robotHaveBall(std::vector<SSLRobot*> robots);
//    bool cyrusHaveBall(std::vector<SSLRobot*> robots);
    bool robotCanKick(SSLRobot * robot);
    SSLRobot* whichRobotCanKick(); // Null : none
    std::vector<SSLRobot*> nearestRobotToBall(std::vector<SSLRobot*> robots);
    std::vector<SSLRobot*> nearestRobotToPoint(std::vector<SSLRobot*> robots,Vector2D point);
    std::vector<SSLRobot*> nearestRobotToRobot(std::vector<SSLRobot*> robots,SSLRobot * robot);
    bool isRobotSameSide(SSLRobot*, SSLRobot*);
    bool isRobotAhead(SSLRobot*, SSLRobot*);


// LEVEL 2 : ROBOT & BALL ------------------------------------------------------------------
    std::vector<SSLRobot*> cyrusCanMakePass();
    std::vector<SSLRobot*> opponentCanMakePass(std::vector<SSLRobot*> cyrusRobots,std::vector<SSLRobot*> opponentRobots);
    SSLRobot* cyrusCanMakeGoal(std::vector<SSLRobot*> cyrusRobots,std::vector<SSLRobot*> opponentRobots,std::vector<int>& goalPoints);
    SSLRobot* opponentCanMakeGoal(std::vector<SSLRobot*> cyrusRobots,std::vector<SSLRobot*> opponentRobots,std::vector<int>& goalPoints);
    SSLRobot* RobotIsForceToKick();

// LEVEL 2 : ROBOT & ROBOT ------------------------------------------------------------------
    std::vector<SSLRobot*> nearestRobotsToBlockRobot(std::vector<SSLRobot*> cyrusRobots,std::vector<SSLRobot*> opponentRobots); // nazdiketrain robot be khate beine robot harif va darvaze
    std::vector<SSLRobot*> nearestRobotsToMarkRobot(std::vector<SSLRobot*> cyrusRobots,std::vector<SSLRobot*> opponentRobots); // nazdiktarin robot be robot

// LEVEL 3 : PREDICTION ---------------------------------------------------------------------

//    std::vector<SSLRobot*> nearestRobotsToBlockKickedBall();
//    std::vector<SSLRobot*> nearestRobotsCanCutOffBall();
  //  Vector3D bestTranslocationForPass();
  //  Vector3D bestTranslocationForShoot();
  //  Vector3D bestTranslocationForMark();
  //  Vector3D bestTranslocationForBlock(std::vector<SSLRobot*> cyrusRobots,SSLRobot * robot);
};

#endif // ANALYZER_H
