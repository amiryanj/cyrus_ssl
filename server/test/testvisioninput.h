#ifndef _TESTSVISIONINPUT_H
#define _TESTSVISIONINPUT_H

#include "../../common/tools/SSLListener.h"
#include "../../common/protoc/vision/cpp/messages_robocup_ssl_wrapper.pb.h"
#include "../../common/protoc/vision/cpp/messages_robocup_ssl_detection.pb.h"


class TestInput
{
public:
    TestInput();

    void updateVisionInput();
    void updateWorldModel();

private:
    SSL_WrapperPacket wrapper_packet;
    SSL_DetectionRobot* our_robots[6];
    SSL_DetectionRobot* opponent_robots[6];
    SSL_DetectionBall* ball;
};

#endif // TESTSERVER_H
