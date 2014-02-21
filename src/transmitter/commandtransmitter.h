#ifndef COMMANDTRANSMITTER_H
#define COMMANDTRANSMITTER_H

#include "../tools/SSLListener.h"
#include "RobotCommandPacket.h"
#include "grsimsender.h"
#include "RobotSerialConnection.h"
#include "general.h"

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


private:
    RobotCommandPacket packets[MAX_ID_NUM];
    bool notSent[MAX_ID_NUM];
    long TransmitCounter;

    RobotSerialConnection* serial;
    GRSimSender* grsim;
};

#endif // COMMANDTRANSMITTER_H
