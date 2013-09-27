/*
 * SSLVision.cpp
 *
 *  Created on: Aug 15, 2013
 *      Author: mostafa
 */

#include "SSLVision.h"
#include <QString>

SSLVision::SSLVision(int port, const string address) : UDP(), SSLListener()
{
    filterModule = VisionFilterModule::getInstance();
}

SSLVision::~SSLVision()
{
}

void SSLVision::check()
{
    Address sender_adress;
    if(this->havePendingData())
    {
        packet.length = this->recv(packet.buffer, MAX_BUFFER_SIZE, sender_adress);
        cerr << "One Packet is received. size = " << packet.length << endl;
        this->parse(this->packet);
        updateKalmanModule();
    }

}

void SSLVision::parse(IPPacket &packet)
{
	wrapper.Clear();
    wrapper.ParseFromArray(packet.buffer, packet.length);
}

void SSLVision::updateKalmanModule()
{
	//TODO: update world model from wrapper    
    if(wrapper.has_detection())
    {
        for(int i=0; i< wrapper.detection().robots_blue_size(); i++)
        {
            SSL_DetectionRobot Robot=wrapper.detection().robots_blue(i);
            tmp_frame.setToCurrentTime();
            tmp_frame.position = Vector3D(Robot.x(), Robot.y(), Robot.orientation());
            filterModule->setRobotFrame(Blue, Robot.robot_id(), tmp_frame);
        }

        for(int i=0; i< wrapper.detection().robots_yellow_size(); i++)
        {
            SSL_DetectionRobot Robot=wrapper.detection().robots_yellow(i);
            tmp_frame.setToCurrentTime();
            tmp_frame.position = Vector3D(Robot.x(), Robot.y(), Robot.orientation());
            filterModule->setRobotFrame(Yellow, Robot.robot_id(), tmp_frame);
        }

        for(int i=0; i< wrapper.detection().balls_size(); i++)
        {
            SSL_DetectionBall Ball=wrapper.detection().balls(i);
            //uint dataTime = time.currentTime().second()*1000 + time.currentTime().msec();
            //emit parsedBallData(i,QVector2D(Ball.x(),Ball.y()), dataTime);
        }
    }
    if(wrapper.has_geometry())
    {
        SSL_GeometryData geometryData = wrapper.geometry();
        // and so on
    }
}
