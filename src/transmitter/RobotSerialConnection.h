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
//#include "../../thirdparty/SSLException.h"
#include "RobotCommandPacket.h"
using namespace std;

class RobotSerialConnection {
public:
    RobotSerialConnection(const char * serialPortName, unsigned int baudrate);
    void sendRobotData(int robotID, RobotCommandPacket &packet);
	virtual ~RobotSerialConnection();
private:
    serialib serial;
};

#endif /* SERIALCONNECTION_H_ */
