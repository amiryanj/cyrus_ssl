#ifndef _TESTSERVER_H
#define _TESTSERVER_H

#include "../../common/tools/SSLListener.h"
#include "../../common/protoc/vision/cpp/messages_robocup_ssl_wrapper.pb.h"
#include "../../common/protoc/vision/cpp/messages_robocup_ssl_detection.pb.h"


class TestServer : public SSLListener
{
public:
    TestServer();

    void check();

private:
    SSL_WrapperPacket wrapper_packet;
};

#endif // TESTSERVER_H
