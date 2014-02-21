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
}


SSLVision::~SSLVision()
{
}

void SSLVision::check()
{
    Address sender_adress;
    if(this->havePendingData())
    {
        this->_packet.length = this->recv(_packet.buffer, MAX_BUFFER_SIZE, sender_adress);
        cerr << "Vision Packet received . Size = " << this->_packet.length << endl;
        this->parse(this->_packet);
        updateFilterModule();
    }

}

void SSLVision::parse(IPPacket &p)
{
	wrapper.Clear();
    wrapper.ParseFromArray(p.buffer, p.length);
}

void SSLVision::updateFilterModule()
{
	//TODO: update world model from wrapper    
    if(wrapper.has_detection())
    {        
        for(int i=0; i< wrapper.detection().robots_blue_size(); i++)
        {
            SSL_DetectionRobot Robot = wrapper.detection().robots_blue(i);
            _tmp_frame.setToCurrentTimeMilliSec();
            _tmp_frame.position = Vector3D(Robot.x(), Robot.y(), Robot.orientation());
            _tmp_frame.confidence = Robot.confidence();
            filterModule->setRobotFrame(Blue, Robot.robot_id(), _tmp_frame);

        }

        for(int i=0; i< wrapper.detection().robots_yellow_size(); i++)
        {
            SSL_DetectionRobot Robot = wrapper.detection().robots_yellow(i);
            _tmp_frame.setToCurrentTimeMilliSec();
            _tmp_frame.position = Vector3D(Robot.x(), Robot.y(), Robot.orientation());
            _tmp_frame.confidence = Robot.confidence();
            filterModule->setRobotFrame(Yellow, Robot.robot_id(), _tmp_frame);
        }

        for(int i=0; i< wrapper.detection().balls_size(); i++)
        {
            SSL_DetectionBall Ball=wrapper.detection().balls(i);
            _tmp_frame.setToCurrentTimeMilliSec();
            _tmp_frame.position = Vector2D(Ball.x(), Ball.y()).to3D();
            filterModule->setBallFrame(_tmp_frame);
        }
    }
    if(wrapper.has_geometry())
    {
        SSL_GeometryData geometryData = wrapper.geometry();
        // and so on
    }
}
