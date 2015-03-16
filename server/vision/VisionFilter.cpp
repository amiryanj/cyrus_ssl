#include "VisionFilter.h"
#include "../definition/SSLBall.h"
#include "../paramater-manager/parametermanager.h"

VisionFilter* VisionFilter::module = NULL;

VisionFilter *VisionFilter::getInstance()
{
    if(module == NULL)
        module = new VisionFilter();
    return module;
}

VisionFilter::VisionFilter()
{
    // initializing filter objects
    for(int i=0; i<NUM_TEAMS; ++i)
        for(int j=0; j<MAX_ID_NUM; ++j)
            robotFilter[i][j] = new RobotFilter();

    ballFilter = new BallFilter();

    for (int i=0; i<MAX_CAMERA_COUNT; i++)
        last_frame_time[i] = 0;

    ParameterManager* pm = ParameterManager::getInstance();
    file.open(pm->get<string>("debug.ball").c_str());
}

VisionFilter::~VisionFilter()
{
    file.close();
}

void VisionFilter::check()
{
    for(int tm=0; tm<NUM_TEAMS; ++tm)
        for(int i=0; i<MAX_ID_NUM; ++i) {
            robotFilter[tm][i]->runFilter();
        }

    ballFilter->runFilter();

    updateWorldModel();

}


void VisionFilter::updateWorldModel()
{
    for(int i=0; i<NUM_TEAMS; ++i)
        for(int j=0; j<MAX_ID_NUM; ++j)
        {
            world->updateRobotState((SSL::Color)i, j,robotFilter[i][j]->m_filteredPosition,
                                                  robotFilter[i][j]->m_filteredSpeed);
            world->updateRobotAvailability((SSL::Color)i, j, robotFilter[i][j]->isOnField());
        }

    world->updateBallState(0, ballFilter->m_filteredPosition,
                           ballFilter->m_filteredVelocity, ballFilter->m_acceleration);

}

void VisionFilter::update(const SSL_WrapperPacket &packet)
{
    if(packet.has_detection())
    {
        if( packet.detection().camera_id() < MAX_CAMERA_COUNT )
        {
            double frame_time = packet.detection().t_capture();
            if( frame_time <=  last_frame_time[packet.detection().camera_id()] ) {
                cerr << "Warning: Decayed packet !!!!" << endl;
                return;
            }
            else
                last_frame_time[packet.detection().camera_id()] = frame_time;
        }

        Frame temp_frame;
        temp_frame.camera_id = packet.detection().camera_id();
        temp_frame.frame_number = packet.detection().frame_number();

//        temp_frame.setToCurrentTimeMilliSec();
        temp_frame.timeStampMilliSec = packet.detection().t_capture() * 1000.0;

        for(int i=0; i < packet.detection().robots_blue_size(); i++)
        {
            SSL_DetectionRobot Robot = packet.detection().robots_blue(i);
            temp_frame.position = Vector3D(Robot.x(), Robot.y(), Robot.orientation());
            temp_frame.confidence = Robot.confidence();
            robotFilter[SSL::Blue][Robot.robot_id()]->putNewFrame(temp_frame);
        }

        for(int i=0; i< packet.detection().robots_yellow_size(); i++)
        {
            SSL_DetectionRobot Robot = packet.detection().robots_yellow(i);
            temp_frame.position = Vector3D(Robot.x(), Robot.y(), Robot.orientation());
            temp_frame.confidence = Robot.confidence();
            robotFilter[SSL::Yellow][Robot.robot_id()]->putNewFrame(temp_frame);
        }

        vector<Frame> balls_vec;
        for(int i=0; i< packet.detection().balls_size(); i++)
        {
            SSL_DetectionBall Ball = packet.detection().balls(i);
            temp_frame.position = Vector2D(Ball.x(), Ball.y()).to3D();
            temp_frame.confidence = Ball.confidence();
            balls_vec.push_back(temp_frame);

//            file <<i << " , " << (long)temp_frame.timeStampMilliSec<< " , ";
//            file << Ball.x() <<" , " << Ball.y() << endl;
        }

        if(balls_vec.empty()) {
            cout << "Warning:: No ball exists in current frame" << endl;
        }
        else if(balls_vec.size() == 1) {
            ballFilter->putNewFrame(balls_vec[0]);
        }
        else {
            cout << "Warning:: More than One ball exist in current frame" << endl;
            ballFilter->putNewFrameWithManyBalls(balls_vec);
        }
    }
    if(packet.has_geometry())
    {
        SSL_GeometryData geometryData = packet.geometry();
        // and so on
    }
}
