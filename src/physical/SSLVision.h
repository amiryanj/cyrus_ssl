/*
 * SSLVision.h
 *
 *  Created on: Aug 15, 2013
 *      Author: mostafa
 */

#ifndef SSLVISION_H_
#define SSLVISION_H_

#include "../thirdparty/sslvision/cpp/messages_robocup_ssl_wrapper.pb.h"
#include "../tools/MulticastListener.h"

class SSLVision : public MulticastListener{
private:
	SSL_WrapperPacket wrapper;
public:
	SSLVision(string address, int port);
	virtual ~SSLVision();
	void parse(IPPacket &packet);
	void updateWorldModel(void* data);
};

#endif /* SSLVISION_H_ */
