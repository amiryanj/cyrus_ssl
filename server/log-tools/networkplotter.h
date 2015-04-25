#ifndef _NETWORKPLOTTER_H
#define _NETWORKPLOTTER_H

#include "../../shared/tools/socket/netraw.h"
#include "../../shared/tools/socket/ippacket.h"
#include "../../shared/proto/plotter/cpp/message_plotter.pb.h"
#include <boost/signals2/mutex.hpp>
#include <vector>

class NetworkPlotter
{
    NetworkPlotter();
    static NetworkPlotter* instance;
public:
    static NetworkPlotter* getInstance();

    bool buildAndSendPacket(string plot_name,
                            vector<double> values, vector<string> legends, double key = -1);

    bool buildAndSendPacket(string plot_name, double value, double key = -1);


    bool sendPacket(Plotter_Packet &packet);

private:
    bool openSocket(int port, string address);


    boost::signals2::mutex mtx_;
    Net::UDP simple_socket;

    int port;
    string address;
};

#endif // NETWORKPLOTTER_H
