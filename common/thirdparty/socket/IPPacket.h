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

#define MAX_BUFFER_SIZE 4096

struct IPPacket {
public:
    IPPacket(int packet_size = MAX_BUFFER_SIZE);
    //~IPPacket();
    int length;
	unsigned short int senderPort;
	string senderAddress;
    char *buffer;
};

#endif /* IPPACKET_H_ */
