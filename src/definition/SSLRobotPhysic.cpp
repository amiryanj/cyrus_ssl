#include "SSLRobotPhysic.h"
#include <cmath>

SSLRobotPhysic::SSLRobotPhysic()
{
    mass = 2.8; // kilo gram
    radius_mm = 90; // mm

    frontFlatAngle_radian = 30.0 * (M_PI/180.0);
    max_lin_vel_mmps = 3000; // meter * sec^-1
    max_ang_vel_radps = 120.0 * (M_PI/180.0);
    max_lin_acc_mmps2 = 2000;
    max_ang_acc_rad_ps2 = 80.0 * (M_PI/180.0);

    max_kick_speed_mmps = 8000;
}

SSLRobotPhysic::SSLRobotPhysic(double mass, double radius, double max_lin_vel, double max_ang_vel,
                               double max_lin_acc, double max_ang_acc, double max_kick_speed) :
    mass(mass), radius_mm(radius), max_lin_vel_mmps(max_lin_vel), max_ang_vel_radps(max_ang_vel),
    max_lin_acc_mmps2(max_lin_acc), max_ang_acc_rad_ps2(max_ang_acc), max_kick_speed_mmps(max_kick_speed)

{
}
