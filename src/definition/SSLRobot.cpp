#include "SSLRobot.h"
#include <iostream>
#include <math.h>

SSLRobot::SSLRobot()
{

}

Vector3D SSLRobot::localSpeed() const
{
    Vector3D local_speed;
    //std::cerr << "doubt in correct calculation of local speed";

    // forward speed
    local_speed.x = Speed().x * cos(orien()) + Speed().y * sin(orien());
    // lateral speed
    local_speed.y = Speed().x * sin(orien()) - Speed().y * cos(orien());
    local_speed.teta = Speed().teta;
    return local_speed;

}

double SSLRobot::orien() const
{
    return this->position_.teta;
}
