#ifndef GRSIMSENDER_H
#define GRSIMSENDER_H

#include "thirdparty/socket/netraw.h"
#include "tools/SSLListener.h"
#include "general.h"
#include "definition/RobotCommandPacket.h"
#include "grSim/cpp/grSim_Packet.pb.h"
#include "ai/SSLWorldModel.h"
#include "ai/SSLGame.h"

class GRSimSender: public Net::UDP, public SSLListener
{
public:
    GRSimSender(SSL::Color our_color = OUR_COLOR);

    Color ourColor;
    bool connected;

    bool openSocket(int port = GRSIM_COMMAND_PORT);
    void sendPacket(int robotID, RobotCommandPacket rawPacket);


    void check();
};

#endif // GRSIMSENDER_H
