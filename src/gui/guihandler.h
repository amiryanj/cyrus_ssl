#ifndef GUIPACKETCOLLECTOR_H
#define GUIPACKETCOLLECTOR_H

#include "../tools/SSLListener.h"
#include "cpp/ssl_visualizer.pb.h"
#include "cpp/ssl_world.pb.h"
#include "../ai/SSLWorldModel.h"
#include "../ai/SSLAnalyzer.h"
#include "../ai/SSLGame.h"
#include "thirdparty/socket/netraw.h"
#include "thirdparty/socket/IPPacket.h"
#include <boost/signals2/mutex.hpp>

using namespace google::protobuf;

//using namespace Net;

class GUIHandler : public SSLListener, public Net::UDP
{
public:
    GUIHandler();

    void check();
    void generateWorldPacket();
    void generateAnalyzerPacket();
    void generateGamePacket();
    bool sendPacket(ssl_visualizer_packet* packet);

private:
    ssl_visualizer_packet visualizer_packet;
    ssl_world world_packet;

    boost::signals2::mutex mtx_;

    SSLWorldModel *world();
    SSLAnalyzer *analyzer();
    SSLGame *game();

};

#endif // GUIPACKETCOLLECTOR_H
