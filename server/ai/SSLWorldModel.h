#ifndef _SSLWORLDMODEL_H_
#define _SSLWORLDMODEL_H_

#include "../../common/general.h"
#include "../../common/sslnamespace.h"
#include "../referee/SSLReferee.h"

class SSLTeam;
class SSLBall;
class SSLRobot;

#define MAX_BALL_NUM 3

#define world SSLWorldModel::getInstance()

class SSLWorldModel {
public:
    static SSLWorldModel *getInstance();

    void updateRobotState(SSL::Color color, int ID, Vector3D position, Vector3D speed, bool inField);
    void updateBallState(int ID, Vector2D position, Vector2D speed, Vector2D acceleration);

    SSLTeam* team[2];
    SSLTeam* getTeam(SSL::Color c);

    SSLBall* balls[MAX_BALL_NUM];
    SSLBall* mainBall();

    vector<SSLRobot*> getInFieldRobots();
    vector<SSLRobot*> getInFieldRobotsExcept(SSLRobot* excep);
    vector<SSLRobot*> getInFieldRobotsExcept(SSL::Color color, uint id);

    vector<SSLRobot*> getAllRobots();
    vector<SSLRobot*> getAllRobotsExcept(SSLRobot* excep);
    vector<SSLRobot*> getAllRobotsExcept(SSL::Color color, uint id);

    SSLReferee::RefereeState m_refereeState;
private:
    SSLWorldModel();
    virtual ~SSLWorldModel() {}
    static SSLWorldModel *world_instance;

};

#endif /* SSLWORLDMODEL_H_ */
