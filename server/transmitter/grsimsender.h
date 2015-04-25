#ifndef GRSIMSENDER_H
#define GRSIMSENDER_H

#include "../tools/socket/netraw.h"
#include "ssllistener.h"
#include "../general.h"
#include "../../shared/proto/grsim/cpp/grSim_Commands.pb.h"
#include "../../shared/proto/grsim/cpp/grSim_Packet.pb.h"
#include "../ai/SSLWorldModel.h"
#include "../ai/SSLGame.h"
#include "RobotCommandPacket.h"

class GRSimSender: public Net::UDP
{
public:
    GRSimSender(SSL::Color our_color);

    Color ourColor;
    bool connected;

    bool openSocket();
    bool openSocket(int port);
    void sendPacket(int robotID, RobotCommandPacket rawPacket);


};

#endif // GRSIMSENDER_H
