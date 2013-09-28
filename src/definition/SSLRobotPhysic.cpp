#include "SSLRobotPhysic.h"

SSLRobotPhysic::SSLRobotPhysic()
{
}

SSLRobotPhysic::SSLRobotPhysic(double mass, double radius, double max_lin_vel, double max_ang_vel,
                               double max_lin_acc, double max_ang_acc, double max_kick_speed) :
    mass(mass), radius(radius), max_lin_vel(max_lin_vel), max_ang_vel(max_ang_vel),
    max_lin_acc(max_lin_acc), max_ang_acc(max_ang_acc), max_kick_speed(max_kick_speed)

{
}
