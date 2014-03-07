/*
 * SSLReferee.cpp
 *
 *  Created on: Aug 16, 2013
 *      Author: mostafa
 */

#include "SSLReferee.h"

SSLReferee::SSLReferee(string address, int port) : UDP(), SSLListener()
{
}

SSLReferee::~SSLReferee() {
}

void SSLReferee::parse(IPPacket &packet){
	referee.Clear();
	referee.ParseFromArray(packet.buffer,packet.length);
}
void SSLReferee::updateWorldModel(){
	//TODO update referee object in world model

}