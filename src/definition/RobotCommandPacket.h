#ifndef ROBOTCOMMANDPACKET_H
#define ROBOTCOMMANDPACKET_H

struct RobotCommandPacket
{
public:
    RobotCommandPacket();
    RobotCommandPacket(double v[], double kickPower = 0, bool isForceKick = false, bool isDribbler=false);
    void reset();

    double v[4];
    double kickPower;
    bool isForceKick;
    bool isDribbler;
};

#endif // ROBOTCOMMANDPACKET_H
