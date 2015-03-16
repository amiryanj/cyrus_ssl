#ifndef _SSLVISION_H_
#define _SSLVISION_H_

#include "../../common/thirdparty/socket/IPPacket.h"
#include "../../common/protoc/vision/cpp/messages_robocup_ssl_wrapper.pb.h"

#include "../../common/thirdparty/socket/netraw.h"
#include "robocup_ssl_client.h"

using namespace Net;

#include <pthread.h>


class SSLVision //: public UDP //, public SSLListener
{
    static UDP simple_socket;
    static IPPacket m_temp_packet;    
    pthread_t ssl_vision_thread;

    static RoboCupSSLClient *client;

    static void *check(void *);
    static void updateFilterModule(const SSL_WrapperPacket& wrapper);

public:
    SSLVision(int port = 0, const std::string address = "");
	virtual ~SSLVision();


};

#endif /* _SSLVISION_H_ */
