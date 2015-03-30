#ifndef ROBOTCOMMANDPACKET_H
#define ROBOTCOMMANDPACKET_H

#include "math/vector3d.h"
#include <cmath>

struct RobotCommandPacket
{
public:
    RobotCommandPacket();
    RobotCommandPacket(double v[], double m_kickPower = 0, bool m_isForceKick = false, bool m_isDribbler=false);
    RobotCommandPacket(Vector3D velocity, bool use_new_wheel_angles = true,
                       double m_kickPower = 0, bool m_isForceKick = false, bool m_isDribbler = false);
    void reset();
    void setVelocity(const Vector3D &vel, bool use_new_wheel_angles = true);
    void setWheelVelocity(double v1, double v2, double v3, double v4);

    double m_kickPower;
    bool m_isForceKick;
    bool m_isDribbler;

    bool byWheelSpeed;
    Vector3D getVelocity() const;
    double getWheelSpeed(int i);
    double getWheelAngle(int i);

    RobotCommandPacket& operator= (RobotCommandPacket& other);

private:
    double v[4];
    Vector3D m_velocity;

    void setVelocityByWheels(Vector3D vel, bool use_new_wheel_angles);

    // in clock-wise direction, the wheels are considered.
    // new robot: 1) 33.7   2) -45.0       3) -135.0       4) +146.3
    const static double wheelAngle_1_new = +30.00 * M_PI/180.0;
    const static double wheelAngle_2_new = -45.00 * M_PI/180.0;
    const static double wheelAngle_3_new = -135.0 *M_PI/180.0;
    const static double wheelAngle_4_new = +150.0 *M_PI/180.0;

    // old robot: 1) 33     2) -38          3) -142         4) 147
    const static double wheelAngle_1_old = +33.0 * M_PI/180.0;
    const static double wheelAngle_2_old = -38.0 * M_PI/180.0;
    const static double wheelAngle_3_old = -142.0 *M_PI/180.0;
    const static double wheelAngle_4_old = +147.0 *M_PI/180.0;



};

#endif // ROBOTCOMMANDPACKET_H
