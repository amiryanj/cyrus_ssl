#include "SSLWorldModel.h"
#include "../definition/SSLTeam.h"
#include "../definition/SSLBall.h"
#include "../definition/SSLRobot.h"
#include <vector>

SSLWorldModel* SSLWorldModel::world_instance = NULL;

SSLWorldModel::SSLWorldModel() {
    // TODO Auto-generated constructor stub
    for(int i=0; i< NUM_TEAMS; ++i)
        team[i] = new SSLTeam((Color)i, SSLRobotPhysic());

    for(int i=0; i<MAX_BALL_NUM; i++)
        balls[i] = new SSLBall();
}

SSLWorldModel *SSLWorldModel::getInstance()
{
    if(world_instance==NULL)
        world_instance = new SSLWorldModel();
    return world_instance;
}

SSLTeam *SSLWorldModel::getTeam(Color c)
{
    return team[c];
}

SSLBall* SSLWorldModel::mainBall()
{
    return balls[0];
}

vector<SSLRobot *> SSLWorldModel::all_inFields()
{
    vector<SSLRobot*> all_;
    all_.reserve(MAX_TEAM_PLAYER*2);
    for(int tm = 0; tm < 2;  ++tm)
        if(team[tm]->numInFields() != 0)
            all_.insert(all_.begin(), team[tm]->inFields().size(), team[tm]->inFields().at(0));
    return all_;
}

vector<SSLRobot *> SSLWorldModel::all_inFieldsExcept(SSLRobot *excep)
{
    vector<SSLRobot*> all_;
    try {
        all_.reserve(MAX_TEAM_PLAYER*2 - 1);
        if(excep == NULL)
            throw "Robot is invalid";
        for(int tm = 0; tm < 2;  ++tm)
        {
            if(team[tm]->numInFields() != 0)
            {
                if(excep->color != (Color)tm)
                    all_.insert(all_.begin(), team[tm]->inFields().size(), team[tm]->inFields().at(0));
                else {
                    for(vector<SSLRobot*>::iterator it=team[tm]->inFields().begin(); it !=  team[tm]->inFields().end(); ++it)
                    {
                        SSLRobot* robot = (SSLRobot*) (*it);
                        if(robot->id != excep->id)
                            all_.push_back(robot);
                    }
                }
            }
        }
    }
    catch(const char* msg) {
        cerr << "Exception: SSLWorldmodel: " << msg << endl;
    }
    return all_;
}

vector<SSLRobot *> SSLWorldModel::allRobots()
{
    vector<SSLRobot*> all_;
    all_.reserve(MAX_ID_NUM * 2);
    for(int tm = 0; tm < 2;  ++tm)
        for(int i=0; i< MAX_ID_NUM; i++)
            all_.push_back(team[tm]->robot[i]);
    return all_;
}

vector<SSLRobot *> SSLWorldModel::allRobotsExcept(SSLRobot *excep)
{
    vector<SSLRobot*> all_;
    all_.reserve(MAX_ID_NUM * 2);
    for(int tm = 0; tm < 2;  ++tm)
        for(int i=0; i< MAX_ID_NUM; i++) {
            if(excep->color == team[tm]->color && excep->id == team[tm]->robot[i]->id)
                continue;
            all_.push_back(team[tm]->robot[i]);
        }
    return all_;
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
    if(available) {
        team[color]->robot[ID]->isInField = true;
    }
    else {
        team[color]->robot[ID]->getOutOfField();
    }

}

void SSLWorldModel::updateBallState(int ID, Vector2D position, Vector2D speed)
{
    if(ID >= MAX_BALL_NUM)
        ID = MAX_BALL_NUM - 1;
    balls[ID]->setPosition(position);
    balls[ID]->setSpeed(speed);
}
