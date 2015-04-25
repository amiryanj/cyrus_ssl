#include "cyrusserverpackethandler.h"
#include "../shared/proto/vision/cpp/messages_robocup_ssl_wrapper.pb.h"
#include <iostream>

CyrusServerPacketHandler::CyrusServerPacketHandler(QObject *parent)
    : QObject(parent)
{
    socket.joinNetwork("127.0.0.1", 4001);

    connect(&socket, SIGNAL(dataPacketReceived(QByteArray)), this, SLOT(processCyrusPacket(QByteArray)));
}

void CyrusServerPacketHandler::processCyrusPacket(QByteArray data_)
{
    SSL_WrapperPacket wrapper;
    wrapper.Clear();
    wrapper.ParseFromArray(data_.data(), data_.length());

    if(wrapper.has_detection())
    {
        for(int i=0; i < wrapper.detection().robots_blue_size(); i++)
        {
            SSL_DetectionRobot Robot = wrapper.detection().robots_blue(i);

        }

        for(int i=0; i< wrapper.detection().robots_yellow_size(); i++)
        {
            SSL_DetectionRobot Robot = wrapper.detection().robots_yellow(i);
        }

//        vector<Frame> balls_vec;
        for(int i=0; i< wrapper.detection().balls_size(); i++)
        {
            SSL_DetectionBall Ball = wrapper.detection().balls(i);
        }
    }
    if(wrapper.has_geometry())
    {
        SSL_GeometryData geometryData = wrapper.geometry();
        // and so on
    }

}
