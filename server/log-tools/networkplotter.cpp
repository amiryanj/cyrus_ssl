#include "networkplotter.h"
#include "../paramater-manager/parametermanager.h"

using namespace std;
NetworkPlotter* NetworkPlotter::instance = NULL;

NetworkPlotter::NetworkPlotter()
{
    ParameterManager* pm = ParameterManager::getInstance();
    port = pm->get<int>("network.plotter_port");
    address = pm->get<string>("network.plotter_address");
    openSocket(port, address);
}

NetworkPlotter *NetworkPlotter::getInstance()
{
    if(instance == NULL) {
        instance = new NetworkPlotter();
    }
    return instance;
}

bool NetworkPlotter::buildAndSendPacket(string plot_name, double value, double key)
{
    if( ParameterManager::getInstance()->get<bool>("network.plotter_enabled") == false)
        return false;
    Plotter_Packet packet;

    packet.set_name(plot_name);
    packet.add_values(value);
    packet.add_legends(plot_name);

    if(key >= 0)
        packet.set_key(key);

    this->sendPacket(packet);
}

bool NetworkPlotter::buildAndSendPacket(string plot_name, vector<double> values, vector<string> legends, double key)
{
    if( ParameterManager::getInstance()->get<bool>("network.plotter_enabled") == false)
        return false;
    Plotter_Packet packet;
    //            required string name = 1;
    //            repeated double values = 2;
    //            optional double key  = 3;
    //            repeated string legends = 4;
    //            required bool clear_history = 5;
    //            optional string sender_name = 6;

    packet.set_name(plot_name);
    for(int i=0; i<values.size(); i++)  {
        packet.add_values(values[i]);
    }
    for(int i=0; i<values.size(); i++)  {
        packet.add_legends(legends[i]);
    }
    if(key >= 0)
        packet.set_key(key);
    this->sendPacket(packet);
}


bool NetworkPlotter::openSocket(int port, string address)
{
    simple_socket.close();
    if(!simple_socket.open(port, true, true))  {
        cerr << "Unable to open UDP network port (Plotter) : "<< port << endl;
        return false;
    }

    Net::Address multiaddr, interface;
    multiaddr.setHost(address.c_str(), port);
    interface.setAny();

    if(!simple_socket.addMulticast(multiaddr, interface))  {
        cerr << "Unable to setup UDP multicast." << endl ;
    }  else  {
        cout << "Visualizer UDP network successfully configured. Multicast address= " << port << endl;
    }
    return true;
}

bool NetworkPlotter::sendPacket(Plotter_Packet &packet)
{
    string buffer;
    packet.set_sender_name("Cyrus Server");
    packet.SerializeToString(&buffer);
    Net::Address multiaddr;
    multiaddr.setHost(address.c_str(), port);
    bool result;
    mtx_.lock();
    result = simple_socket.send(buffer.c_str(), buffer.length(), multiaddr);
    mtx_.unlock();

    if (result==false)  {
//        cerr << "Sending Plotter data failed (maybe too large?). Size was: " << buffer.length() << endl;
    }  else  {
//        cout << buffer.length() << " Bytes of ( Visualizer Packet ) sent." << endl;
    }
    return result;
}

