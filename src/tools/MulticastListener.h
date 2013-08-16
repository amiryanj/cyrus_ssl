/*
 * MulticastListener.h
 *
 *  Created on: Aug 16, 2013
 *      Author: mostafa
 */

#ifndef MULTICASTLISTENER_H_
#define MULTICASTLISTENER_H_

#include <string>
#include "../thirdparty/socket/MulticastReciever.h"
#include "../definition/WorldModel.h"
#include "SSLListener.h"

using namespace std;

class MulticastListener : public SSLListener{
private:
	MulticastReciever reciever;
public:
	MulticastListener(string addres, int port);
	virtual ~MulticastListener();
	virtual void parse(IPPacket& packet)=0;
	void check();
};

#endif /* MULTICASTLISTENER_H_ */
