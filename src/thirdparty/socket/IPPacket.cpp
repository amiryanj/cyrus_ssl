/*
 * IPPacket.cpp
 *
 *  Created on: Aug 16, 2013
 *      Author: mostafa
 */

#include "IPPacket.h"
/*
IPPacket::IPPacket() {
}
*/
//IPPacket::~IPPacket() {

//}


IPPacket::IPPacket(int packet_size)
{
    this->buffer = new char[packet_size];
    this->length = packet_size;
}
