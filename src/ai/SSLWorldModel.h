/*
 * WorldModel.h
 *
 *  Created on: Aug 14, 2013
 *      Author: mostafa, javad
 */

#ifndef SSLWORLDMODEL_H_
#define SSLWORLDMODEL_H_

#include "../general.h"
#include "definition/SSLTeam.h"
#include "definition/SSLBall.h"
#include "../tools/stdlist.h"

class SSLWorldModel {
public:
    void updateRobotState(Color color, int ID, Vector3D position, Vector3D speed);
    void updateRobotAvailability(Color color, int ID, bool available);
    void updateBallState(int ID, Vector2D position, Vector2D speed);
    static SSLWorldModel *getInstance();

    SSLTeam* team[2];
    SSLTeam* getTeam(Color c);

    SSLBall *mainBall();
    SSLBall* ball; // should be ommited
    STDVector<SSLBall*> allBalls;
    STDVector<SSLRobot*> allRobots();

private:
    SSLWorldModel();
    virtual ~SSLWorldModel();

    static SSLWorldModel *world;
};

#endif /* SSLWORLDMODEL_H_ */
