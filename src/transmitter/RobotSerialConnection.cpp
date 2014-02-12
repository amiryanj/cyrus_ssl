/*
 * SerialConnection.cpp
 *
 *  Created on: Aug 14, 2013
 *      Author: mostafa
 */

#include "RobotSerialConnection.h"


RobotSerialConnection::RobotSerialConnection(const char * serialPortName, unsigned int baudrate)
  throw(SSLException)
{

    if (serial.Open(serialPortName,baudrate) != 1)
    {
    	throw SSLException("failed to open serial device");
        //std::cerr << "device " << serialPortName <<" failed to open" << std::endl;
    }
}

void RobotSerialConnection::sendRobotData(int robotID, RobotCommandPacket &packet)
{
    unsigned char byteArray[7];
    //start byte
    byteArray[0] = '*';

    //robotID, motor spin and dribbler state
    byteArray[1] = (unsigned char) ( (robotID + (
            (packet.getWheelSpeed(1)> 0 ? 0:1) * 1 +
            (packet.getWheelSpeed(2)> 0 ? 0:1) * 2 +
            (packet.getWheelSpeed(3)> 0 ? 0:1) * 4 +
            (packet.getWheelSpeed(4)> 0 ? 0:1) * 8) * 16)
            & 0x000000FF);

    //velocity bytes
    for (int i = 1; i <= 4; i++)
    {
        byteArray[i + 1] = (unsigned char)( (int)(fabs(round(packet.getWheelSpeed(i)*255))) & 0x000000FF );
    }

    //kick power byte
    byteArray[6] = (unsigned char) ((packet.isForceKick) ? 255 :
    		fabs(round(packet.kickPower * 255))
	);

    //transmit data to serial port
    serial.Write(byteArray,7);
}

RobotSerialConnection::~RobotSerialConnection(){
    serial.Close();
}
