/*
 * SerialConnection.cpp
 *
 *  Created on: Aug 14, 2013
 *      Author: mostafa
 */

#include "RobotSerialConnection.h"
#include <stdio.h>
#include "../../shared/utility/generalmath.h"
#include "../debug-tools/networkplotter.h"

RobotSerialConnection::RobotSerialConnection(const char * serialPortName, unsigned int baudrate)
{    
    try {
#if QT_VERSION >= 0x050000
        serial = new QSerialPort(serialPortName);
        serial->setBaudRate(baudrate);
        if (!serial->open(QIODevice::WriteOnly))
#else
        serial = new serialib;
        if(!serial->Open(serialPortName, baudrate))
#endif
                throw "failed to open serial device";
    }
    catch (const char* msg)  {
        cerr << "Exception: " << "RobotSerialConnection" << msg << endl;
    }
}

void RobotSerialConnection::sendRobotData(int robotID, RobotCommandPacket &packet)
{
    const static int packet_size = 7;
    unsigned char byteArray[packet_size];
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
    // old version
//    byteArray[6] = (unsigned char) ((packet.m_isForceKick) ? 255 :
//    		fabs(round(packet.m_kickPower * 255))
    byteArray[6] = ((packet.m_kickPower > 0)) * 85;

    printf( "(time=%.6f) Robot[%d] (m1=%4d  m2=%4d  m3=%4d  m4=%4d) [Vx=%.4f, Vy=%.4f, Wz=%.4f] ",
            currentTimeMSec()/1000.0,
            robotID,
            ((((byteArray[1] & 0x10)!=0)*2)-1)*byteArray[2],
            ((((byteArray[1] & 0x20)!=0)*2)-1)*byteArray[3],
            ((((byteArray[1] & 0x40)!=0)*2)-1)*byteArray[4],
            ((((byteArray[1] & 0x80)!=0)*2)-1)*byteArray[5],
            packet.getVelocity().X(),
            packet.getVelocity().Y(),
            packet.getVelocity().Teta());

//    if(packet.m_kickPower > 0)
//        printf("Kick Power: %.3f", packet.m_kickPower);
    cout << endl;
    //transmit data to serial port
#if QT_VERSION >= 0x050000
    serial->write(byteArray, packet_size);
#else
    serial->Write(byteArray, packet_size);
#endif
}

RobotSerialConnection::~RobotSerialConnection()
{
#if QT_VERSION >= 0x050000
    serial->close();
#else
    serial->Close();
#endif
}
