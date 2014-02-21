#include "SSLTeam.h"

#include "SSLRobot.h"

SSLTeam::SSLTeam(const Side side, const Color color, const SSLRobotPhysic &physic)
{

    for(int i = 0; i < MAX_ID_NUM; i++ )
    {
        this->robot[i]= new SSLRobot(this);
        robot[i]->id = i;
        robot[i]->color = color;        
        robot[i]->isInField = false;
        robot[i]->physic = physic;
    }

    this->side = side;
    this->color = color;

}

std::string SSLTeam::colorStr()
{
    return (color == Yellow)? "Yellow":"Blue";
}

vector<SSLRobot *> SSLTeam::inFieldRobots()
{
    vector<SSLRobot*> robotList;
    robotList.reserve(MAX_TEAM_PLAYER);
    for( int i = 0; i < MAX_ID_NUM ; ++i )
        if(this->robot[i]->isInField == true)
            robotList.push_back(robot[i]);
    return robotList;
}


unsigned int SSLTeam::numInFieldRobots() const
{
    int count=0;
    for(int i=0;i<MAX_ID_NUM;++i)
        if(this->robot[i]->isInField == true)
            count++;
    return count;
}
