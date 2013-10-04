/*
 * SSLWorldModel.cpp
 *
 *  Created on: Aug 14, 2013
 *      Author: mostafa
 */

#include "SSLWorldModel.h"

SSLWorldModel* SSLWorldModel::world = NULL;

SSLWorldModel *SSLWorldModel::getInstace()
{
    if(world==NULL)
        world = new SSLWorldModel();
    return world;
}


SSLWorldModel::SSLWorldModel() {
	// TODO Auto-generated constructor stub
    for(int i=0; i< NUM_TEAMS; ++i)
        team[i] = new SSLTeam((Side)i, (Color)i, SSLRobotPhysic());

    ball = new SSLBall();

}

SSLWorldModel::~SSLWorldModel() {
	// TODO Auto-generated destructor stub
}

void SSLWorldModel::updateRobotState(Color color, int ID, Vector3D position, Vector3D speed)
{
    //TODO not implemented yet
    this->team[color]->robot[ID]->setPosition(position);
    this->team[color]->robot[ID]->setSpeed(speed);
}

