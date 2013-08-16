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

    if (lib.Open(serialPortName,baudrate) != 1)
    {
    	throw SSLException("failed to open serial device");
        //std::cerr << "device " << serialPortName <<" failed to open" << std::endl;
    }
}

void RobotSerialConnection::sendRobotData(int robotID, SSLRobotPacket &packet)
{
    unsigned char byteArray[7];
    //start byte
    byteArray[0] = '*';

    //robotID, motor spin and dribbler state
    byteArray[1] = (unsigned char) ( (robotID + (
            (packet.v[0]> 0 ? 0:1) * 1 +
            (packet.v[1]> 0 ? 0:1) * 2 +
            (packet.v[2]> 0 ? 0:1) * 4 +
            (packet.v[3]> 0 ? 0:1) * 8) * 16)
            & 0x000000FF);

    //velocity bytes
    for (int i = 0; i < 4; i++)
    {
        byteArray[2+i] = (unsigned char)( (int)(fabs(round(packet.v[i]*255))) & 0x000000FF );
    }

    //kick power byte
    byteArray[6] = (unsigned char) ((packet.isForceKick) ? 255 :
    		fabs(round(packet.kickPower * 255))
	);

    //transmit data to serial port
    lib.Write(byteArray,7);
}

RobotSerialConnection::~RobotSerialConnection(){
	lib.Close();
}
