
#include "SSLRobotPacket.h"

SSLRobotPacket::SSLRobotPacket()
{
    reset();
}

SSLRobotPacket::SSLRobotPacket(double v[], double kickPower, bool isForceKick, bool isDribbler)
{
    this->v[0] = v[0];
    this->v[1] = v[1];
    this->v[2] = v[2];
    this->v[3] = v[3];

    this->kickPower = kickPower;
    this->isForceKick = isForceKick;
    this->isDribbler = isDribbler;
}

void SSLRobotPacket::reset(){
    this->v[0] = 0;
    this->v[1] = 0;
    this->v[2] = 0;
    this->v[3] = 0;

    this->kickPower = 0;
    this->isForceKick = 0;
    this->isDribbler = 0;
}
