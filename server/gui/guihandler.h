#ifndef _GUIHANDLER_H
#define _GUIHANDLER_H

#include "ssllistener.h"
#include "../../shared/proto/visualizer/cpp/ssl_visualizer.pb.h"
#include "../../shared/proto/visualizer/cpp/ssl_world.pb.h"
#include "../ai/SSLWorldModel.h"
#include "../ai/SSLAnalyzer.h"
#include "../ai/SSLGame.h"
#include "../tools/socket/netraw.h"
#include "../tools/socket/ippacket.h"
#include <boost/signals2/mutex.hpp>
#include <QMutex>
using namespace google::protobuf;

//using namespace Net;

class GUIHandler : public SSLListener, public Net::UDP
{
    GUIHandler();
    static GUIHandler* instance;
public:
    static GUIHandler* getInstance();
    bool openSocket();
    bool openSocket(int port, string address);

    void check();

    ssl_visualizer_packet* generateVisualizerPacket();
    void testVisualizer();
    void generateWorldPacket(ssl_world_packet* packet);
    void generateAnalyzerPacket(ssl_analyzer_packet* packet);
    void generatePlannerPacket(ssl_planner_packet* packet);
    void generateDecisionPacket(ssl_decision_packet* packet);

    bool sendPacket(const ssl_visualizer_packet &p);

private:
//    ssl_visualizer_packet visualizer_packet;
//    ssl_world_packet world_packet;

    QMutex mtx_;
};

#endif // _GUIHANDLER_H
