/*
 * SerialConnection.h
 *
 *  Created on: Aug 14, 2013
 *      Author: mostafa
 */

#ifndef SERIALCONNECTION_H_
#define SERIALCONNECTION_H_


#if QT_VERSION >= 0x050000
#include <QSerialPort>
#else
#include "../tools/serialib/serialib.h"
#endif

#include "../general.h"
#include "RobotCommandPacket.h"
using namespace std;

class RobotSerialConnection {
public:
    RobotSerialConnection(const char * serialPortName, unsigned int baudrate);
    void sendRobotData(int robotID, RobotCommandPacket &packet);
	virtual ~RobotSerialConnection();
private:
#if QT_VERSION >= 0x050000
    QSerialPort* serial;
#else
    serialib* serial;
#endif
};

#endif /* SERIALCONNECTION_H_ */
