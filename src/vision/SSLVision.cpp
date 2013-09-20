/*
 * SSLVision.cpp
 *
 *  Created on: Aug 15, 2013
 *      Author: mostafa
 */

#include "SSLVision.h"

SSLVision::SSLVision(string address, int port) : MulticastListener(address,port)
{
    world = SSLWorldModel::getInstace();
    now = time(0);
}

SSLVision::~SSLVision() {
}

void SSLVision::parse(IPPacket &packet){
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
            //uint dataTime = time.currentTime().second()*1000 + time.currentTime().msec();
            //emit parsedRobotData(blue_color,Robot.robot_id(),
                //QVector3D(Robot.x(),Robot.y(),Robot.orientation()), dataTime);
        }

        for(int i=0; i< wrapper.detection().robots_yellow_size(); i++)
        {
            SSL_DetectionRobot Robot=wrapper.detection().robots_yellow(i);
            //uint dataTime = time.currentTime().second()*1000 + time.currentTime().msec();
            //emit parsedRobotData(yellow_color,Robot.robot_id(),
                //QVector3D(Robot.x(),Robot.y(),Robot.orientation()), dataTime);
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
