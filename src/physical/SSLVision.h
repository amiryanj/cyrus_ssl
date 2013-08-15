/*
 * SSLVision.h
 *
 *  Created on: Aug 15, 2013
 *      Author: mostafa
 */

#ifndef SSLVISION_H_
#define SSLVISION_H_

#include "../thirdparty/sslvision/cpp/messages_robocup_ssl_wrapper.pb.h"

class SSLVision {
public:
	SSLVision();
	virtual ~SSLVision();
	SSL_WrapperPacket wrapper;
};

#endif /* SSLVISION_H_ */
