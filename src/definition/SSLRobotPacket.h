#ifndef SSLROBOTPACKET_H
#define SSLROBOTPACKET_H

class SSLRobotPacket
{
public:
    SSLRobotPacket();
    SSLRobotPacket(double v[], double kickPower = 0, bool isForceKick = false, bool isDribbler=false);
    void reset();

    double v[4];
    double kickPower;
    bool isForceKick;
    bool isDribbler;
};

#endif // SSLROBOTPACKET_H
