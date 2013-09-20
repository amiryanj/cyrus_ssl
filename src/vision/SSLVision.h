/*
 * SSLVision.h
 *
 *  Created on: Aug 15, 2013
 *      Author: mostafa
 */

#ifndef SSLVISION_H_
#define SSLVISION_H_

#include <ctime>
#include "../thirdparty/sslvision/cpp/messages_robocup_ssl_wrapper.pb.h"
#include "../tools/MulticastListener.h"
#include "../ai/SSLWorldModel.h"

class SSLVision : public MulticastListener{
private:
    SSL_WrapperPacket wrapper;
    SSLWorldModel* world;

    time_t now;

public:
	SSLVision(string address, int port);
	virtual ~SSLVision();
	void parse(IPPacket &packet);
//    void updateWorldModel();
    void updateKalmanModule();
};

#endif /* SSLVISION_H_ */
