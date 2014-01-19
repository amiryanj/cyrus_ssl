#ifndef SSLROBOTPHYSIC_H
#define SSLROBOTPHYSIC_H

class SSLRobotPhysic
{
public:
    SSLRobotPhysic();
    SSLRobotPhysic(double mass, double radius, double max_lin_vel, double max_ang_vel,
                    double max_lin_acc, double max_ang_acc, double max_kick_speed);
    double mass;
    double radius; // mm
    double frontFlatAngle; // in radian
    double max_lin_vel; // meter * sec^-1
    double max_ang_vel;
    double max_lin_acc;
    double max_ang_acc;

    double max_kick_speed;

};

#endif // SSLROBOTPHYSIC_H
