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

class SerialConnection {
public:
	SerialConnection(const char * serialPortName, unsigned int baudrate);
	void sendRobotData(int robotID, SSLRobotPacket &packet);
	virtual ~SerialConnection();
private:
	serialib lib;
};

#endif /* SERIALCONNECTION_H_ */
