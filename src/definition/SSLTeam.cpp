#include "SSLTeam.h"

#include "SSLRobot.h"

SSLTeam::SSLTeam(const Side side, const Color color, const SSLRobotPhysic &physic)
{

    for(int i = 0; i < MAX_ID_NUM; i++ )
    {
        this->robot[i]= new SSLRobot(this);
        robot[i]->id = i;
        robot[i]->color = color;        
        robot[i]->physic = physic;
        robot[i]->getOutOfField();
    }

    this->side = side;
    this->color = color;

}

std::string SSLTeam::colorStr()
{
    return (color == Yellow)? "Yellow":"Blue";
}

// this method returns in-field robots of the team, sorted by their ID's
vector<SSLRobot *> SSLTeam::inFields()
{
    vector<SSLRobot*> robotList;
    robotList.reserve(MAX_TEAM_PLAYER);
    for( int i = 0; i < MAX_ID_NUM ; ++i )
        if(this->robot[i]->isInField)
            robotList.push_back(robot[i]);
    return robotList;
}

vector<SSLRobot *> SSLTeam::allRobots()
{
    vector<SSLRobot*> robotList;
    robotList.reserve(MAX_ID_NUM);
    for( int i = 0; i < MAX_ID_NUM ; ++i )
        robotList.push_back(robot[i]);
    return robotList;
}

unsigned int SSLTeam::numInFields() const
{
    int count=0;
    for(int i=0;i<MAX_ID_NUM;++i)
        if(this->robot[i]->isInField == true)
            count++;
    return count;
}
