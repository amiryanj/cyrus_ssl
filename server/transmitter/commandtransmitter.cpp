#include "commandtransmitter.h"

#include <iostream>
#include "RobotSerialConnection.h"
#include "../paramater-manager/parametermanager.h"

using namespace std;

CommandTransmitter* CommandTransmitter::transmitter = NULL;

CommandTransmitter::CommandTransmitter()
{
//    ParameterManager::getInstance()->get<>;
    OLD_ID_NUMS.push_back(0);
    OLD_ID_NUMS.push_back(4);
    OLD_ID_NUMS.push_back(6);
    OLD_ID_NUMS.push_back(10);

    try {
        this->serial = new RobotSerialConnection(SERIAL_PORT, 38400);
        this->grsim = new GRSimSender(SSLGame::getInstance()->ourColor());
        grsim->openSocket();
        this->type = SERIAL;  // default is grsim

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

void CommandTransmitter::buildAndSendPacket(int id, Vector3D &vel, float kickPower)
{
    bool useNewRobotWheelAngles = true;

    for(uint i=0; i<OLD_ID_NUMS.size(); i++) {
        if(id == OLD_ID_NUMS[i]) {
            useNewRobotWheelAngles = false;
            break;
        }
    }

    RobotCommandPacket pkt(vel, useNewRobotWheelAngles, kickPower);
    pkt.byWheelSpeed=true;
    this->send(id, pkt);
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

void CommandTransmitter::clear()
{
    for(int i=0; i<MAX_ID_NUM; i++) {
        notSent[i] = false;
    }
}

void CommandTransmitter::check()
{
    this->flush();
}
