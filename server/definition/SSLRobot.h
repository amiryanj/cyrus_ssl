#ifndef _SSLROBOT_H
#define _SSLROBOT_H

#include "../../shared/general.h"
#include "SSLObject.h"
#include "SSLTeam.h"

struct SSLRobotState {
                                /// @variable unit
    short    camera_id;
    double   timeStamp_second;  // second
    Vector3D position;          // mili meter
    Vector3D displacement;      // mili meter
    Vector3D velocity;          // mili meter per second
    Vector3D acceleration;      // mili meter per second^2
};

struct SSLRobotPhysics
{
public:
    SSLRobotPhysics() {   }

    SSLRobotPhysics(float mass, float radius, float max_lin_vel, float max_ang_vel,
                                   float max_lin_acc, float max_ang_acc, float max_kick_speed) :
        mass(mass), radius_mm(radius), max_lin_vel_mmps(max_lin_vel),
        max_ang_vel_radps(max_ang_vel), max_lin_acc_mmps2(max_lin_acc),
        max_ang_acc_rad_ps2(max_ang_acc), max_kick_speed_mmps(max_kick_speed) {  }

    float mass;
    float radius_mm; // mm
    float front_flat_angle_radian; // in radian
    float max_lin_vel_mmps; // millimeter * sec^-1
    float max_ang_vel_radps;
    float max_lin_acc_mmps2;
    float max_ang_acc_rad_ps2;

    float max_kick_speed_mmps;

};


class SSLRobot : public SSLObject<Vector3D>
{
public:
    SSLRobot(SSLTeam* team = 0);
    SSLTeam* team;

    unsigned int id;
    Color color;
    std::string colorStr();
    void getOutOfField();

    bool isInField;

    Vector3D localSpeed() const;
    float orien() const;

    SSLRobotPhysics physic;

};

#endif // SSLROBOT_H
