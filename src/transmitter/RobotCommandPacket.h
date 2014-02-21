#ifndef ROBOTCOMMANDPACKET_H
#define ROBOTCOMMANDPACKET_H

#include "../tools/vector3d.h"

struct RobotCommandPacket
{
public:
    RobotCommandPacket();
    RobotCommandPacket(double v[], double kickPower = 0, bool isForceKick = false, bool isDribbler=false);
    RobotCommandPacket(double vx, double vy, double wz,
                       double kickPower = 0, bool isForceKick = false, bool isDribbler = false);
    RobotCommandPacket(Vector3D velocity, double kickPower = 0, bool isForceKick = false, bool isDribbler = false);
    void reset();
    void setVelocity(const Vector3D &vel);
    void setVelocity(double vx, double vy, double wz);
    void setMotorVelocity(double v1, double v2, double v3, double v4);

    double kickPower;
    bool isForceKick;
    bool isDribbler;

    bool byWheelSpeed;
    Vector3D getVelocity() const;
    double getWheelSpeed(int i);

    RobotCommandPacket& operator= (RobotCommandPacket& other);

private:
    double v[4];
    Vector3D Velocity;

};

#endif // ROBOTCOMMANDPACKET_H
