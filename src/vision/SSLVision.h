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
#include "VisionFilterModule.h"
#include "frame.h"
#include <thirdparty/socket/IPPacket.h>
#include <iostream>

using namespace std;

#include "netraw.h"
using namespace Net;

class SSLVision : public SSLListener, public UDP{
private:
    SSL_WrapperPacket wrapper;
    VisionFilterModule* filterModule;

    frame tmp_frame;

public:
    SSLVision(int port, const string address);
	virtual ~SSLVision();

    void check();
	void parse(IPPacket &packet);

    IPPacket packet;

    void updateKalmanModule();
};

#endif /* SSLVISION_H_ */
