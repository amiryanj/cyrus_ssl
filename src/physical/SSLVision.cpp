/*
 * SSLVision.cpp
 *
 *  Created on: Aug 15, 2013
 *      Author: mostafa
 */

#include "SSLVision.h"

SSLVision::SSLVision(string address, int port) : MulticastListener(address,port){
}

SSLVision::~SSLVision() {
}

void SSLVision::parse(IPPacket &packet){
	wrapper.Clear();
	wrapper.ParseFromArray(packet.buffer,packet.length);
}
void SSLVision::updateWorldModel()
{
	//TODO: update world model from wrapper
}
