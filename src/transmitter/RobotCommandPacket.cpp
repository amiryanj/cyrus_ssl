#include "RobotCommandPacket.h"
#include <iostream>
#include <cmath>
#include "../general.h"

using namespace std;
// in clockwise turn
double RobotCommandPacket::wheelAngle_1 = +45.0 * M_PI/180.0;
double RobotCommandPacket::wheelAngle_2 = -45.0 * M_PI/180.0;
double RobotCommandPacket::wheelAngle_3 = -135 * M_PI/180.0;
double RobotCommandPacket::wheelAngle_4 = +135.0 * M_PI/180.0;

RobotCommandPacket::RobotCommandPacket()
{
    reset();
}

RobotCommandPacket::RobotCommandPacket(double v[], double kickPower, bool isForceKick, bool isDribbler)
{
    this->v[0] = v[0];
    this->v[1] = v[1];
    this->v[2] = v[2];
    this->v[3] = v[3];

    this->kickPower = kickPower;
    this->isForceKick = isForceKick;
    this->isDribbler = isDribbler;
}

RobotCommandPacket::RobotCommandPacket(double vx, double vy, double wz,
                                       double kickPower, bool isForceKick, bool isDribbler)
{
    this->Velocity.set(vx, vy, wz);

    this->kickPower = kickPower;
    this->isForceKick = isForceKick;
    this->isDribbler = isDribbler;
}

RobotCommandPacket::RobotCommandPacket(Vector3D velocity, double kickPower, bool isForceKick, bool isDribbler)
{
    this->Velocity = velocity;

    this->kickPower = kickPower;
    this->isForceKick = isForceKick;
    this->isDribbler = isDribbler;
}

void RobotCommandPacket::reset(){
    this->v[0] = 0;
    this->v[1] = 0;
    this->v[2] = 0;
    this->v[3] = 0;

    this->Velocity.setZero();

    this->kickPower = 0;
    this->isForceKick = 0;
    this->isDribbler = 0;
}

void RobotCommandPacket::setVelocity(const Vector3D &vel)
{
    this->Velocity = vel;
    this->byWheelSpeed = false;
}

void RobotCommandPacket::setVelocity(double vx, double vy, double wz)
{
    this->Velocity.set(vx, vy, wz);

    this->byWheelSpeed = false;
}

void RobotCommandPacket::setVelocityByWheels(double vx, double vy, double wz)
{
    // by Jacobian Matrix
    v[0] = cos(wheelAngle_1) * vx + sin(wheelAngle_1)* vy + ROBOT_RADIUS* wz;
    v[1] = cos(wheelAngle_2) * vx + sin(wheelAngle_2)* vy + ROBOT_RADIUS* wz;
    v[2] = cos(wheelAngle_3) * vx + sin(wheelAngle_3)* vy + ROBOT_RADIUS* wz;
    v[3] = cos(wheelAngle_4) * vx + sin(wheelAngle_4)* vy + ROBOT_RADIUS* wz;

    this->byWheelSpeed = true;
}

void RobotCommandPacket::setWheelVelocity(double v1, double v2, double v3, double v4)
{
    v[0] = v1;
    v[1] = v2;
    v[2] = v3;
    v[3] = v4;

    this->byWheelSpeed = true;
}

RobotCommandPacket &RobotCommandPacket::operator =(RobotCommandPacket &other)
{
    this->kickPower = other.kickPower;
    this->isForceKick = other.isForceKick;
    this->isDribbler = other.isDribbler;
    this->byWheelSpeed = other.byWheelSpeed;

    this->Velocity = other.Velocity;
    this->v[0] = other.v[0];
    this->v[1] = other.v[1];
    this->v[2] = other.v[2];
    this->v[3] = other.v[3];

}


Vector3D RobotCommandPacket::getVelocity() const
{
    return this->Velocity;
}

double RobotCommandPacket::getWheelSpeed(int i)
{
    try {
        if(i < 1 || i > 4)
            throw "Invalid Wheel Speed Number request" ;
        return v[i-1];
    }
    catch (const char* msg) {
        cerr << "Exception: RobotCommandPacket: " << msg << endl;
        return 0;
    }
}

double RobotCommandPacket::getWheelAngle(int i)
{
    try {
        if(i < 1 || i > 4)
            throw "Invalid Wheel Speed Number request" ;
        switch(i) {
        case 1:
            return wheelAngle_1 * 180.0/M_PI;
        case 2:
            return wheelAngle_2 * 180.0/M_PI;
        case 3:
            return wheelAngle_3 * 180.0/M_PI;
        case 4:
            return wheelAngle_4 * 180.0/M_PI;
        }
    }
    catch (const char* msg) {
        cerr << "Exception: RobotCommandPacket: " << msg << endl;
        return 0;
    }

}
