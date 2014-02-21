#ifndef GUIPACKETCOLLECTOR_H
#define GUIPACKETCOLLECTOR_H

#include "../tools/SSLListener.h"
#include "cpp/ssl_visualizer.pb.h"
#include "cpp/ssl_world.pb.h"
#include "../ai/SSLWorldModel.h"
#include "../ai/SSLAnalyzer.h"
#include "../ai/SSLGame.h"
#include "../thirdparty/socket/netraw.h"
#include "../thirdparty/socket/IPPacket.h"
#include <boost/signals2/mutex.hpp>

using namespace google::protobuf;

//using namespace Net;

class GUIHandler : public SSLListener, public Net::UDP
{
    GUIHandler();
    static GUIHandler* instance;
public:
    static GUIHandler* getInstance();

    bool openSocket(int port = VISUALIZER_PORT);

    void check();

    ssl_visualizer_packet* generateVisualizerPacket();

    void generateWorldPacket(ssl_world_packet* packet);
    void generateAnalyzerPacket(ssl_analyzer_packet* packet);
    void generatePlannerPacket(ssl_planner_packet* packet);
    void generateDecisionPacket(ssl_decision_packet* packet);

    bool sendPacket(const ssl_visualizer_packet &p);

private:
//    ssl_visualizer_packet visualizer_packet;
//    ssl_world_packet world_packet;

    boost::signals2::mutex mtx_;

    SSLWorldModel *world();
    SSLAnalyzer *analyzer();
    SSLGame *game();

};

#endif // GUIPACKETCOLLECTOR_H
