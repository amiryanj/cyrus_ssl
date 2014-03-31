#ifndef SSLWORLDMODEL_H_
#define SSLWORLDMODEL_H_

#include "../general.h"
#include "../referee/SSLReferee.h"
#include "../definition/Concepts.h"

class SSLTeam;
class SSLBall;
class SSLRobot;

#define MAX_BALL_NUM 3

#define world SSLWorldModel::getInstance()

class SSLWorldModel {
public:
    void updateRobotState(SSL::Color color, int ID, Vector3D position, Vector3D speed);
    void updateRobotAvailability(SSL::Color color, int ID, bool available);
    void updateBallState(int ID, Vector2D position, Vector2D speed);
    static SSLWorldModel *getInstance();

    SSLTeam* team[2];
    SSLTeam* getTeam(SSL::Color c);

    SSLBall* balls[MAX_BALL_NUM];
    SSLBall* mainBall();

    vector<SSLRobot*> all_inFields();
    vector<SSLRobot*> all_inFieldsExcept(SSLRobot* excep);

    vector<SSLRobot*> allRobots();
    vector<SSLRobot*> allRobotsExcept(SSLRobot* excep);

    SSLReferee::RefereeState m_refereeState;

private:
    SSLWorldModel();
    virtual ~SSLWorldModel();
    static SSLWorldModel *world_instance;

};

#endif /* SSLWORLDMODEL_H_ */
