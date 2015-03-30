#ifndef _TESTSVISIONINPUT_H
#define _TESTSVISIONINPUT_H

#include "../../common/tools/SSLListener.h"
#include "../../common/protoc/vision/cpp/messages_robocup_ssl_wrapper.pb.h"
#include "../../common/protoc/vision/cpp/messages_robocup_ssl_detection.pb.h"


class TestVisionInput : public SSLListener
{
public:
    TestVisionInput();

    void check();

private:
    SSL_WrapperPacket wrapper_packet;
};

#endif // TESTSERVER_H
