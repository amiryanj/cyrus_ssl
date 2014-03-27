/*
 * SSLVision.h
 *
 *  Created on: Aug 15, 2013
 *      Author: mostafa
 */

#ifndef SSLVISION_H_
#define SSLVISION_H_

#include "../general.h"
#include "VisionFilterModule.h"
#include "frame.h"
#include "../thirdparty/socket/IPPacket.h"
#include "../thirdparty/sslvision/cpp/messages_robocup_ssl_wrapper.pb.h"

#include "../thirdparty/socket/netraw.h"

using namespace Net;

class SSLVision : public SSLListener, public UDP
{
private:
    VisionFilter* filterModule;

//    void parse(IPPacket &p);
    void updateFilterModule(const SSL_WrapperPacket& wrapper);

    //    SSL_WrapperPacket wrapper;
//    frame m_temp_frame;
    IPPacket m_temp_packet;

public:
    SSLVision(int port = 0, const std::string address = "");
	virtual ~SSLVision();

    void check();


};

#endif /* SSLVISION_H_ */
