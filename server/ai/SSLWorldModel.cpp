#include "SSLWorldModel.h"
#include "../definition/SSLTeam.h"
#include "../definition/SSLBall.h"
#include "../definition/SSLRobot.h"
#include "../paramater-manager/parametermanager.h"
#include <vector>

SSLWorldModel* SSLWorldModel::world_instance = NULL;

SSLWorldModel::SSLWorldModel()
{
    m_refereeState = SSLReferee::ForceStart;

    for(int i=0; i<MAX_BALL_NUM; i++)
        balls[i] = new SSLBall();

    ParameterManager* pm = ParameterManager::getInstance();
    SSLRobotPhysics cyrus_physics;
    cyrus_physics.mass        = pm->get<float>("robot_properties.cyrus.mass"); // kilo gram
    cyrus_physics.radius_mm   = pm->get<float>("robot_properties.cyrus.radius"); // kilo gram
    cyrus_physics.max_kick_speed_mmps = pm->get<float>("robot_properties.cyrus.max_kick_speed");
    cyrus_physics.front_flat_angle_radian
            = pm->get<float>("robot_properties.cyrus.front_flat_angle_deg") * (M_PI/180.0);

    cyrus_physics.max_lin_vel_mmps    = pm->get<float>("robot_properties.cyrus.max_linear_velocity");
    cyrus_physics.max_lin_acc_mmps2   = pm->get<float>("robot_properties.cyrus.max_angular_acceleration");
    cyrus_physics.max_ang_vel_radps   = pm->get<float>("robot_properties.cyrus.max_angular_velocity")* (M_PI/180.0);
    cyrus_physics.max_ang_acc_rad_ps2 = pm->get<float>("robot_properties.cyrus.max_angular_acceleration")* (M_PI/180.0);

    SSLRobotPhysics enemy_physics;
    enemy_physics.mass        = pm->get<float>("robot_properties.enemy.mass"); // kilo gram
    enemy_physics.radius_mm   = pm->get<float>("robot_properties.enemy.radius"); // kilo gram
    enemy_physics.max_kick_speed_mmps = pm->get<float>("robot_properties.enemy.max_kick_speed");
    enemy_physics.front_flat_angle_radian
            = pm->get<float>("robot_properties.enemy.front_flat_angle_deg") * (M_PI/180.0);

    enemy_physics.max_lin_vel_mmps    = pm->get<float>("robot_properties.enemy.max_linear_velocity");
    enemy_physics.max_lin_acc_mmps2   = pm->get<float>("robot_properties.enemy.max_angular_acceleration");
    enemy_physics.max_ang_vel_radps   = pm->get<float>("robot_properties.enemy.max_angular_velocity")* (M_PI/180.0);
    enemy_physics.max_ang_acc_rad_ps2 = pm->get<float>("robot_properties.enemy.max_angular_acceleration")* (M_PI/180.0);

    for(int i=0; i< NUM_TEAMS; ++i) {
        if(pm->get<int>("game.our_color") == i)     {
            team[i] = new SSLTeam((Color)i, cyrus_physics);
        }  else {
            team[i] = new SSLTeam((Color)i, enemy_physics);
        }
    }
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

vector<SSLRobot *> SSLWorldModel::getInFieldRobots()
{
    vector<SSLRobot*> all_;
    all_.reserve(MAX_TEAM_PLAYER * 2);
    for(int tm = 0; tm < 2;  ++tm) {
        vector<SSLRobot*> teamRobots = team[tm]->getInFieldRobots();
        all_.insert(all_.end(), teamRobots.begin(), teamRobots.end());
    }
    return all_;
}

vector<SSLRobot *> SSLWorldModel::getInFieldRobotsExcept(SSLRobot *excep)
{
    if(excep == NULL)
        return getInFieldRobots();
    return getInFieldRobotsExcept(excep->color, excep->id);

}

vector<SSLRobot *> SSLWorldModel::getInFieldRobotsExcept(Color color, uint id)
{
    vector<SSLRobot*> all_;
    all_.reserve(MAX_TEAM_PLAYER*2 - 1);
    for(int tm = 0; tm < 2;  ++tm)
    {
        vector<SSLRobot*> teamRobots = team[tm]->getInFieldRobots();
        if(color != (Color)tm) {
            all_.insert(all_.end(), teamRobots.begin(), teamRobots.end());
        }
        else {
            for(vector<SSLRobot*>::iterator it=teamRobots.begin(); it != teamRobots.end(); ++it)
            {
                SSLRobot* robot = (SSLRobot*) (*it);
                if(robot->id != id)
                    all_.push_back(robot);
            }
        }
    }
    return all_;
}

vector<SSLRobot *> SSLWorldModel::getAllRobots()
{
    vector<SSLRobot*> all_;
    all_.reserve(MAX_ID_NUM * 2);
    for(int tm = 0; tm < 2;  ++tm)
        for(int i=0; i< MAX_ID_NUM; i++)
            all_.push_back(team[tm]->robot[i]);
    return all_;
}

vector<SSLRobot *> SSLWorldModel::getAllRobotsExcept(SSLRobot *excep)
{
    if(excep == NULL)
        return getAllRobots();

    return getAllRobotsExcept(excep->color, excep->id);
}

vector<SSLRobot *> SSLWorldModel::getAllRobotsExcept(SSL::Color color, uint id)
{
    vector<SSLRobot*> all_;
    all_.reserve(MAX_ID_NUM * 2);
    for(int tm = 0; tm < 2;  ++tm)
        for(int i=0; i< MAX_ID_NUM; i++) {
            if(color == team[tm]->color && id == team[tm]->robot[i]->id)
                continue;
            else
                all_.push_back(team[tm]->robot[i]);
        }
    return all_;
}

void SSLWorldModel::updateRobotState(Color color, int ID, Vector3D position, Vector3D speed, bool inField)
{
    //TODO not implemented yet
    this->team[color]->robot[ID]->setPosition(position);
    this->team[color]->robot[ID]->setSpeed(speed);
    team[color]->robot[ID]->isInField = inField;
    if( !inField )  {
        team[color]->robot[ID]->getOutOfField();
    }
}

void SSLWorldModel::updateBallState(int ID, Vector2D position, Vector2D speed, Vector2D acceleration)
{
    if(ID >= MAX_BALL_NUM)
        ID = MAX_BALL_NUM - 1;
    balls[ID]->setPosition(position);
    balls[ID]->setSpeed(speed);
    balls[ID]->setAcceleration(acceleration);
}
