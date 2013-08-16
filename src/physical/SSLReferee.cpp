/*
 * SSLReferee.cpp
 *
 *  Created on: Aug 16, 2013
 *      Author: mostafa
 */

#include "SSLReferee.h"

SSLReferee::SSLReferee(string address, int port) : MulticastListener(address,port){
}

SSLReferee::~SSLReferee() {
}

void SSLReferee::parse(IPPacket &packet){
	referee.Clear();
	referee.ParseFromArray(packet.buffer,packet.length);
}
void SSLReferee::updateWorldModel(void* data){
	//TODO update referee object in world model
}
