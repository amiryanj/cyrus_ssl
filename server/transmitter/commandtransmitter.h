#ifndef COMMANDTRANSMITTER_H
#define COMMANDTRANSMITTER_H

#include "SSLListener.h"
#include "RobotCommandPacket.h"
#include "grsimsender.h"
#include "RobotSerialConnection.h"
#include "../general.h"

class CommandTransmitter : public SSLListener
{
    CommandTransmitter();
    static CommandTransmitter* transmitter;

public:
    enum TransmitType {SERIAL = 0, GRSIM = 1};
    static CommandTransmitter* getInstance();

    void send(int robot_id, RobotCommandPacket packet);
    void flush();

    void check();

    TransmitType type;

    void buildAndSendPacket(int id, Vector3D &vel, float kickPower = 0);
private:
    RobotCommandPacket packets[MAX_ID_NUM];
    bool notSent[MAX_ID_NUM];
    long TransmitCounter;

    RobotSerialConnection* serial;
    GRSimSender* grsim;

    vector<int> OLD_ID_NUMS;
};

#endif // COMMANDTRANSMITTER_H
