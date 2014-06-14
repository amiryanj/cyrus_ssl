#include "packetreceiver.h"
#include "proto/cpp/ssl_visualizer.pb.h"
#include "proto/cpp/ssl_world.pb.h"
#include <iostream>
#include <QDebug>

using namespace std;

PacketReceiver::PacketReceiver()
{
    connect(&socket, SIGNAL(readyRead()), this, SLOT(processPendingData()));
    timer.setInterval(2000);
    timer.start();
    connect(&timer, SIGNAL(timeout()), this, SLOT(timerTimeout()));
}

void PacketReceiver::check()
{

}

void PacketReceiver::timerTimeout()
{
    this->joinNetwork();
    timer.start();
}

bool PacketReceiver::joinNetwork(QString IP, int port)
{
    socket.close();
    socket.bind(port, QUdpSocket::ShareAddress);
    bool joinResultFlag = socket.joinMulticastGroup(QHostAddress(IP));
    if(joinResultFlag)
        qDebug() << "Successfully connected to Cyrus Server ..." ;
    else
        qDebug() << "Failed to connect Cyrus Server !!!" ;
    return joinResultFlag;
}

void PacketReceiver::processPendingData()
{
    qDebug() << "new data packet received";
    while (socket.hasPendingDatagrams())
    {
        receivedData.resize(socket.pendingDatagramSize());
        socket.readDatagram(receivedData.data(), receivedData.size());
    }

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

