#include "SSLRobot.h"
#include <iostream>
#include <math.h>
#include <QVector3D>

SSLRobot::SSLRobot()
{

}

QVector3D SSLRobot::localSpeed() const
{
    QVector3D local_speed;
    std::cerr << "doubt in correct calculation of local speed";
    // forward speed
    local_speed.setX(speed.x()*cos(orien_radian()) + speed.y()*sin(orien_radian()));
    // lateral speed
    local_speed.setY(speed.x()*sin(orien_radian()) - speed.y()*cos(orien_radian()));
    local_speed.setZ(speed.z());
    return local_speed;

}

double SSLRobot::orien_radian() const
{
    return this->position.z();
}
