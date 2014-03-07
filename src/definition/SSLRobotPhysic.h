#ifndef SSLROBOTPHYSIC_H
#define SSLROBOTPHYSIC_H

class SSLRobotPhysic
{
public:
    SSLRobotPhysic();
    SSLRobotPhysic(double mass, double radius_mm, double max_lin_vel_mmps, double max_ang_vel_radps,
                    double max_lin_acc_mmps2, double max_ang_acc_rad_ps2, double max_kick_speed_mmps);
    double mass;
    double radius_mm; // mm
    double frontFlatAngle_radian; // in radian
    double max_lin_vel_mmps; // millimeter * sec^-1
    double max_ang_vel_radps;
    double max_lin_acc_mmps2;
    double max_ang_acc_rad_ps2;

    double max_kick_speed_mmps;

};

#endif // SSLROBOTPHYSIC_H
