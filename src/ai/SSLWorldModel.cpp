/*
 * SSLWorldModel.cpp
 *
 *  Created on: Aug 14, 2013
 *      Author: mostafa, javad
 */

#include "SSLWorldModel.h"
#include "definition/SSLRobot.h"

SSLWorldModel* SSLWorldModel::world = NULL;

SSLWorldModel::SSLWorldModel() {
    // TODO Auto-generated constructor stub
    for(int i=0; i< NUM_TEAMS; ++i)
        team[i] = new SSLTeam((Side)i, (Color)i, SSLRobotPhysic());

    ball = new SSLBall();

}

SSLWorldModel *SSLWorldModel::getInstance()
{
    if(world==NULL)
        world = new SSLWorldModel();
    return world;
}

SSLTeam *SSLWorldModel::getTeam(Color c)
{
    return team[c];
}

SSLBall* SSLWorldModel::mainBall()
{
    if(this->allBalls.empty())
        return NULL;
    return allBalls[0];
}

STDVector<SSLRobot *> SSLWorldModel::allRobots()
{
    STDVector<SSLRobot*> all_;
    for(int tm = 1; tm < 2;  ++tm)
    {
        for(int i = 0; i< team[tm]->numInFieldRobots(); ++i)
        {
            all_.append(team[tm]->inFieldRobots()[i]);
        }
    }
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

void SSLWorldModel::updateRobotAvailability(Color color, int ID, bool available)
{
    team[color]->robot[ID]->isInField = available;
}

void SSLWorldModel::updateBallState(int ID, Vector2D position, Vector2D speed)
{
    this->ball->setPosition(position);
    this->ball->setSpeed(speed);
}

