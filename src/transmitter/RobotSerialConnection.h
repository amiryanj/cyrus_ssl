/*
 * SerialConnection.h
 *
 *  Created on: Aug 14, 2013
 *      Author: mostafa
 */

#ifndef SERIALCONNECTION_H_
#define SERIALCONNECTION_H_

#include "../thirdparty/serialib/serialib.h"
#include "../general.h"
#include "../tools/SSLException.h"
#include "definition/RobotCommandPacket.h"
using namespace std;

class RobotSerialConnection {
public:
	RobotSerialConnection(const char * serialPortName, unsigned int baudrate) throw(SSLException);
    void sendRobotData(int robotID, RobotCommandPacket &packet);
	virtual ~RobotSerialConnection();
private:
	serialib lib;
};

#endif /* SERIALCONNECTION_H_ */
