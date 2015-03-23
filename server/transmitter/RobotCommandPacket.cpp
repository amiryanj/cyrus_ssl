#include "RobotCommandPacket.h"
#include <iostream>
#include <cmath>
#include "../general.h"

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

    this->m_kickPower = kickPower;
    this->m_isForceKick = isForceKick;
    this->m_isDribbler = isDribbler;
}

RobotCommandPacket::RobotCommandPacket(Vector3D velocity, bool use_new_wheel_angles,
                                       double kickPower, bool isForceKick, bool isDribbler)
{
    this->m_velocity = velocity;

    this->setVelocityByWheels(velocity, use_new_wheel_angles);

    this->m_kickPower = kickPower;
    this->m_isForceKick = isForceKick;
    this->m_isDribbler = isDribbler;

    this->setVelocity(velocity, use_new_wheel_angles);
}

void RobotCommandPacket::reset(){
    this->v[0] = 0;
    this->v[1] = 0;
    this->v[2] = 0;
    this->v[3] = 0;

    this->m_velocity.setZero();

    this->m_kickPower = 0;
    this->m_isForceKick = 0;
    this->m_isDribbler = 0;
}

void RobotCommandPacket::setVelocity(const Vector3D &vel, bool use_new_wheel_angles)
{
    this->m_velocity = vel;
    this->setVelocityByWheels(vel, use_new_wheel_angles);
    this->byWheelSpeed = false;
}

void RobotCommandPacket::setVelocityByWheels(Vector3D vel, bool use_new_wheel_angles)
{
    float omega_coeff = ROBOT_RADIUS * 0.01;
    // by Jacobian Matrix
    if(use_new_wheel_angles) {
        v[0] = cos(wheelAngle_1_new) * vel.X() + sin(wheelAngle_1_new)* vel.Y() + omega_coeff * vel.Teta();
        v[1] = cos(wheelAngle_2_new) * vel.X() + sin(wheelAngle_2_new)* vel.Y() + omega_coeff * vel.Teta();
        v[2] = cos(wheelAngle_3_new) * vel.X() + sin(wheelAngle_3_new)* vel.Y() + omega_coeff * vel.Teta();
        v[3] = cos(wheelAngle_4_new) * vel.X() + sin(wheelAngle_4_new)* vel.Y() + omega_coeff * vel.Teta();
    }
    else {
        v[0] = cos(wheelAngle_1_old) * vel.X() + sin(wheelAngle_1_old)* vel.Y() + omega_coeff * vel.Teta();
        v[1] = cos(wheelAngle_2_old) * vel.X() + sin(wheelAngle_2_old)* vel.Y() + omega_coeff * vel.Teta();
        v[2] = cos(wheelAngle_3_old) * vel.X() + sin(wheelAngle_3_old)* vel.Y() + omega_coeff * vel.Teta();
        v[3] = cos(wheelAngle_4_old) * vel.X() + sin(wheelAngle_4_old)* vel.Y() + omega_coeff * vel.Teta();
    }

    // test for clamping wheel velocities
    for(int i=0; i<4; i++) {
        if(fabs(v[i]) > 1) {
            float temp = fabs(v[i]) * 1.001;
            for(int j=0; j<4; j++) {
                v[j] = v[j]/temp;
            }
        }
    }

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
    this->m_kickPower = other.m_kickPower;
    this->m_isForceKick = other.m_isForceKick;
    this->m_isDribbler = other.m_isDribbler;
    this->byWheelSpeed = other.byWheelSpeed;

    this->m_velocity = other.m_velocity;
    this->v[0] = other.v[0];
    this->v[1] = other.v[1];
    this->v[2] = other.v[2];
    this->v[3] = other.v[3];

    return (*this);

}


Vector3D RobotCommandPacket::getVelocity() const
{
    return this->m_velocity;
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
            return wheelAngle_1_new * 180.0/M_PI;
        case 2:
            return wheelAngle_2_new * 180.0/M_PI;
        case 3:
            return wheelAngle_3_new * 180.0/M_PI;
        case 4:
            return wheelAngle_4_new * 180.0/M_PI;
        }
    }
    catch (const char* msg) {
        cerr << "Exception: RobotCommandPacket: " << msg << endl;
    }
    return 0;

}
