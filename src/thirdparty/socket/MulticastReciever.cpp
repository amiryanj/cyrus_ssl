/*
 * MulticastReciever.cpp
 *
 *  Created on: Aug 16, 2013
 *      Author: mostafa
 *
 *
 *   C++ sockets on Unix and Windows
 *   Copyright (C) 2002
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#include "MulticastReciever.h"
#include <iostream>          // For cout and cerr

MulticastReciever::MulticastReciever(string address, int port, int size)
: UDPSocket(port)
{
	joinGroup(address);
	this->port = port;
	this->address = address;
	this->size = size;
	packet.buffer = new char[size];
}

MulticastReciever::~MulticastReciever() {
	leaveGroup(address);
	delete (char*)(packet.buffer);
}

IPPacket& MulticastReciever::read(){
	packet.length = recvFrom(packet.buffer,size,packet.senderAddress,packet.senderPort);
	return packet;
}

