#include "packetreceiver.h"
#include "protoc/visualizer/cpp/ssl_visualizer.pb.h"
#include "protoc/visualizer/cpp/ssl_world.pb.h"
#include <iostream>
#include <sys/socket.h>
#include <QDebug>

using namespace std;

PacketReceiver::PacketReceiver()
{
    char opt=1;
    setsockopt(socket.socketDescriptor(), SOL_RAW, SO_REUSEADDR, &opt, sizeof(int));
    connect(&socket, SIGNAL(readyRead()), this, SLOT(processPendingData()));
    timer.setInterval(3000);
   // timer.start();
    connect(&timer, SIGNAL(timeout()), this, SLOT(timerTimeout()));
}

PacketReceiver::~PacketReceiver()
{
    this->disconnectNetwork();
}

void PacketReceiver::setNetworkSettings(int port, QString address)
{
    this->mPort = port;
    this->mAddress = address;
}

void PacketReceiver::timerTimeout()
{
    timer.stop();
    this->joinNetwork();
}

bool PacketReceiver::joinNetwork()
{
    socket.close();
#if QT_VERSION >= 0x050000
    if(socket.bind(QHostAddress::AnyIPv4, mPort, QUdpSocket::ShareAddress))
#else
    if(socket.bind(QHostAddress::Any, mPort, QUdpSocket::ShareAddress))
#endif
        qDebug() << "Binded Successfully" ;
    else
        qDebug() << "Failed to Bind";
    if(socket.state() != QAbstractSocket::BoundState) {
          qDebug() << "Not Bind State";
          timer.start();
    }

    bool joinResultFlag = socket.joinMulticastGroup(QHostAddress(mAddress));
//    if(joinResultFlag)
//        qDebug() << "Successfully connected to Cyrus Server ..." ;
//    else
//        qDebug() << socket.errorString();
//    return joinResultFlag;
    return true;
}

void PacketReceiver::disconnectNetwork()
{
    socket.close();
}

void PacketReceiver::processPendingData()
{

    receivedData.clear();

    while (socket.hasPendingDatagrams())
    {
        receivedData.resize(socket.pendingDatagramSize());
        socket.readDatagram(receivedData.data(), receivedData.size());
    }

    qDebug() << "new data packet received. size # " << receivedData.size();

    if( receivedData.size() == 0 )
        return ;

    timer.start();
    vis_packet.ParseFromArray(receivedData,receivedData.size());
    if(vis_packet.has_world_data())
    {
        ssl_world_packet p = vis_packet.world_data();
        emit newWorldPacket(p);
    }
    if(vis_packet.has_analyzer_data())
    {
        ssl_analyzer_packet p = vis_packet.analyzer_data();
        emit newAnalyzerPacket(p);
    }
    if(vis_packet.has_decision_data())
    {
        ssl_decision_packet p = vis_packet.decision_data();
        emit newDecisionPacket(p);
    }
    if(vis_packet.has_planner_data())  {
        ssl_planner_packet p = vis_packet.planner_data();
        emit newPlannerPacket(p);
    }
}

