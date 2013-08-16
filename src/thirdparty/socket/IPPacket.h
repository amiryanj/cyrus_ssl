/*
 * IPPacket.h
 *
 *  Created on: Aug 16, 2013
 *      Author: mostafa
 */

#ifndef IPPACKET_H_
#define IPPACKET_H_

#include <string>
using namespace std;

struct IPPacket {
public:
	/*IPPacket();
	~IPPacket();*/
	int length;
	unsigned short int senderPort;
	string senderAddress;
	void* buffer;
};

#endif /* IPPACKET_H_ */
