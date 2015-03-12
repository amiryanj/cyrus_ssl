#ifndef _SSLVISION_H_
#define _SSLVISION_H_

#include "../thirdparty/socket/IPPacket.h"
#include "../../protoc/vision/cpp/messages_robocup_ssl_wrapper.pb.h"

#include "../thirdparty/socket/netraw.h"
using namespace Net;

#include <pthread.h>

class SSLVision //: public UDP //, public SSLListener
{
    static UDP udp_socket;
    static IPPacket m_temp_packet;

    pthread_t ssl_vision_thread;

    static void *check(void *);
    static void updateFilterModule(const SSL_WrapperPacket& wrapper);

public:
    SSLVision(int port = 0, const std::string address = "");
	virtual ~SSLVision();


};

#endif /* _SSLVISION_H_ */
