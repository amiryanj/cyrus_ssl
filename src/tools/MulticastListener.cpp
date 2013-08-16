/*
 * MulticastListener.cpp
 *
 *  Created on: Aug 16, 2013
 *      Author: mostafa
 */

#include "MulticastListener.h"

MulticastListener::MulticastListener(string address, int port)
	:reciever(address, port)
{
}

MulticastListener::~MulticastListener() {
}

void MulticastListener::check(){
	IPPacket packet = reciever.read();
	if (packet.length >0) {
		parse(packet);
		updateWorldModel(NULL);
	}
}
