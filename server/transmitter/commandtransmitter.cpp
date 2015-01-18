#include "commandtransmitter.h"

#include <iostream>
#include "RobotSerialConnection.h"

using namespace std;

CommandTransmitter* CommandTransmitter::transmitter = NULL;

CommandTransmitter::CommandTransmitter()
{
    try {
        this->serial = new RobotSerialConnection(SERIAL_PORT, 38400);
        this->grsim = new GRSimSender(SSLGame::getInstance()->ourColor());
        grsim->openSocket();
        this->type = GRSIM;  // default is grsim
    }
    catch (...) {

    }
}

CommandTransmitter *CommandTransmitter::getInstance()
{
    if(transmitter == NULL)
        transmitter= new CommandTransmitter();
    return transmitter;
}

void CommandTransmitter::send(int robot_id, RobotCommandPacket packet)
{
    try {
        if((robot_id > MAX_ID_NUM) || (robot_id <0))
            throw "Invalid ID Number";
        this->packets[robot_id] = packet;
        this->notSent[robot_id] = true;
    }
    catch (const char* msg) {
        cerr << "Exception: CommandTransmitter: " << msg << endl;
    }
}

void CommandTransmitter::flush()
{
    try {
        for(int i = 0; i<MAX_ID_NUM; i++) {
            if(notSent[i])
            {
                if(type == GRSIM) {
                    grsim->sendPacket(i, packets[i]);
                }
                else if(type == SERIAL) {
                    serial->sendRobotData(i, packets[i]);
                }
                else {
                    throw "Sender is unknown ???";
                }
            }
            notSent[i] = false;
        }
    }
    catch (const char* msg) {
        cerr << "Exception: CommandTransmitter: " << msg << endl;
    }
}

void CommandTransmitter::check()
{
    this->flush();
}
