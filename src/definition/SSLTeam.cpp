#include "SSLTeam.h"

SSLTeam::SSLTeam(Side side, Color color, SSLRobotPhysic physic)
{
    for(int i = 0; i < MAX_ID_NUM; i++ )
    {
        this->robot[i]= new SSLRobot();
        robot[i]->id = i;
        robot[i]->color = color;
        robot[i]->colorStr = (color == Yellow)? "Yellow" : "Blue";
        robot[i]->isInField = false;
        robot[i]->physic = physic;
    }

    this->side = side;
    this->color = color;
    colorStr = (color == Yellow)? "Yellow" : "Blue";
}

QList<SSLRobot *> SSLTeam::inFieldRobots()
{
    QList<SSLRobot*> robotList;
    for( int i = 0; i < MAX_ID_NUM ; ++i )
        if(this->robot[i]->isInField == true)
            robotList.append(robot[i]);
    return robotList;
}


uint SSLTeam::numInFieldRobots()
{
    int count=0;
    for(int i=0;i<MAX_ID_NUM;++i)
        if(this->robot[i]->isInField == true)
            count++;
    return count;
}
