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
    void updateRobotPosition(int ID, Color color);
    static SSLWorldModel *getInstace();

    SSLTeam *team[2];
    SSLBall *ball;

private:
    SSLWorldModel();
    virtual ~SSLWorldModel();

    static SSLWorldModel *world;
};

#endif /* SSLWORLDMODEL_H_ */
