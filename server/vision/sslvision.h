#ifndef _SSLVISION_H_
#define _SSLVISION_H_

#include "../../shared/proto/vision/cpp/messages_robocup_ssl_wrapper.pb.h"
#include "../../shared/tools/socket/netraw.h"

#include "robocup_ssl_client.h"

#include <pthread.h>

class SSLVision //: public UDP //, public SSLListener
{
    pthread_t ssl_vision_thread;

    static Net::UDP simple_socket;
    static RoboCupSSLClient *client;

    static void *check(void *);
    static void updateFilterModule(const SSL_WrapperPacket& wrapper);

public:
    SSLVision(int port = 0, const std::string address = "");
	virtual ~SSLVision();

};

#endif /* _SSLVISION_H_ */
