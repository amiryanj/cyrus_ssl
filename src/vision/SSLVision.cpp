/*
 * SSLVision.cpp
 *
 *  Created on: Aug 15, 2013
 *      Author: mostafa
 */

#include "SSLVision.h"

SSLVision::SSLVision(int port, const string address) : UDP(), SSLListener()
{
    filterModule = VisionFilter::getInstance();
    this->open(port, true, true);
    Address multi_, interface_;
    multi_.setHost(address.c_str(), port);
    interface_.setAny();
    this->addMulticast(multi_, interface_);
}

SSLVision::~SSLVision()
{
}

void SSLVision::check()
{
    Address sender_adress;
    if(this->havePendingData())
    {
        m_temp_packet.length = this->recv(m_temp_packet.buffer, MAX_BUFFER_SIZE, sender_adress);
        cout << "Vision-Packet received. Packet Lenght: [" << this->m_temp_packet.length << "]" << endl;

        SSL_WrapperPacket wrapper;
        wrapper.Clear();
        wrapper.ParseFromArray(m_temp_packet.buffer, m_temp_packet.length);

        updateFilterModule(wrapper);
    }
}

void SSLVision::updateFilterModule(const SSL_WrapperPacket &wrapper)
{
	//TODO: update world model from wrapper    
    if(wrapper.has_detection())
    {        
        frame temp_frame;
        for(int i=0; i < wrapper.detection().robots_blue_size(); i++)
        {
            SSL_DetectionRobot Robot = wrapper.detection().robots_blue(i);
            temp_frame.setToCurrentTimeMilliSec();
            temp_frame.position = Vector3D(Robot.x(), Robot.y(), Robot.orientation());
            temp_frame.confidence = Robot.confidence();
            temp_frame.camera_id = wrapper.detection().camera_id();
            filterModule->setRobotFrame(SSL::Blue, Robot.robot_id(), temp_frame);

        }

        for(int i=0; i< wrapper.detection().robots_yellow_size(); i++)
        {
            SSL_DetectionRobot Robot = wrapper.detection().robots_yellow(i);
            temp_frame.setToCurrentTimeMilliSec();
            temp_frame.position = Vector3D(Robot.x(), Robot.y(), Robot.orientation());
            temp_frame.confidence = Robot.confidence();
            temp_frame.camera_id = wrapper.detection().camera_id();
            filterModule->setRobotFrame(SSL::Yellow, Robot.robot_id(), temp_frame);
        }

        for(int i=0; i< wrapper.detection().balls_size(); i++)
        {
            SSL_DetectionBall Ball=wrapper.detection().balls(i);
            temp_frame.setToCurrentTimeMilliSec();
            temp_frame.position = Vector2D(Ball.x(), Ball.y()).to3D();
            filterModule->setBallFrame(temp_frame);
        }
    }
    if(wrapper.has_geometry())
    {
        SSL_GeometryData geometryData = wrapper.geometry();
        // and so on
    }
}
