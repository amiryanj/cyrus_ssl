#include "RobotCommandPacket.h"
#include "iostream"

using namespace std;

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

void RobotCommandPacket::setMotorVelocity(double v1, double v2, double v3, double v4)
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
