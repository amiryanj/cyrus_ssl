#ifndef _SSLVISION_H_
#define _SSLVISION_H_

#include "../../shared/proto/vision/cpp/messages_robocup_ssl_wrapper.pb.h"
#include "robocup_ssl_client.h"

class SSLVision //: public UDP //, public SSLListener
{
    static void *check(void *);
    static void updateFilterModule(const SSL_WrapperPacket& wrapper);

    static RoboCupSSLClient *client;
    static bool idle;

public:
    SSLVision(int port = 0, const std::string address = "");
	virtual ~SSLVision();

    static void setIdle(bool i);

};

#endif /* _SSLVISION_H_ */
