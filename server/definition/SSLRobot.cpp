#include "SSLRobot.h"
#include <iostream>
#include <math.h>

#include "SSLTeam.h"

SSLRobot::SSLRobot(SSLTeam *team)
{
    this->team = team;
    this->m_radius = ROBOT_RADIUS;
}

std::string SSLRobot::colorStr()
{
    return (color == Yellow)? "Yellow":"Blue";
}

void SSLRobot::getOutOfField()
{
    this->setPosition(Vector3D(id* this->m_radius * 2.5 , FIELD_WIDTH /2 *((color==SSL::Blue)? 1:-1)* 1.4, 0.0));
    this->isInField = false;
}

Vector3D SSLRobot::localSpeed() const
{
    Vector3D local_speed;
    //std::cerr << "doubt in correct calculation of local speed";

    // forward speed
    local_speed.setX(Speed().X() * cos(orien()) + Speed().Y() * sin(orien()));
    // lateral speed
    local_speed.setY(Speed().X() * sin(orien()) - Speed().Y() * cos(orien()));
    local_speed.setTeta(Speed().Teta());
    return local_speed;

}

double SSLRobot::orien() const
{
    return this->m_position.Teta();
}
