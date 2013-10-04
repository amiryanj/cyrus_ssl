/*
 * WorldModel.h
 *
 *  Created on: Aug 14, 2013
 *      Author: mostafa
 */

#ifndef SSLWORLDMODEL_H_
#define SSLWORLDMODEL_H_

#include "../general.h"
#include "definition/SSLTeam.h"
#include "definition/SSLBall.h"

class SSLWorldModel {
public:
    void updateRobotState(Color color, int ID, Vector3D position, Vector3D speed);
    void updateBallState(int ID, Vector3D position, Vector3D speed);
    static SSLWorldModel *getInstace();

    SSLTeam *team[2];
    SSLBall *ball;

private:
    SSLWorldModel();
    virtual ~SSLWorldModel();

    static SSLWorldModel *world;
};

#endif /* SSLWORLDMODEL_H_ */
