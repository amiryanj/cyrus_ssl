#ifndef GRSIMSENDER_H
#define GRSIMSENDER_H

#include "../thirdparty/socket/netraw.h"
#include "../tools/SSLListener.h"
#include "../general.h"
#include "RobotCommandPacket.h"
#include "grSim/cpp/grSim_Packet.pb.h"
#include "../ai/SSLWorldModel.h"
#include "../ai/SSLGame.h"

class GRSimSender: public Net::UDP
{
public:
    GRSimSender(SSL::Color our_color);

    Color ourColor;
    bool connected;

    bool openSocket(int port = GRSIM_COMMAND_PORT);
    void sendPacket(int robotID, RobotCommandPacket rawPacket);


};

#endif // GRSIMSENDER_H
