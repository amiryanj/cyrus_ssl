#include "SSLRobot.h"
#include <iostream>
#include <math.h>

#include "SSLTeam.h"

SSLRobot::SSLRobot()
{

}

std::string SSLRobot::colorStr()
{
    return (color == Yellow)? "Yellow":"Blue";
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
    return this->_position.Teta();
}
