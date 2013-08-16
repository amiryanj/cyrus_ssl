/*
 * MulticastReciever.h
 *
 *  Created on: Aug 16, 2013
 *      Author: mostafa
 */

#ifndef MULTICASTRECIEVER_H_
#define MULTICASTRECIEVER_H_

#include "PracticalSocket.h" // For UDPSocket and SocketException
#include "IPPacket.h"

#define MAXBUFFERSIZE 4096     // Longest string to receive

class MulticastReciever : public UDPSocket{
private:
	int port;
	string address;
	int size;
	IPPacket packet;
public:
	MulticastReciever(string address,int port,int size=MAXBUFFERSIZE);
	IPPacket& read();
	virtual ~MulticastReciever();
};

#endif /* MULTICASTRECIEVER_H_ */
