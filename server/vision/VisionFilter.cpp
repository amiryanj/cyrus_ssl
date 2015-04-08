#include "VisionFilter.h"
#include "../definition/SSLBall.h"
#include "../paramater-manager/parametermanager.h"

VisionFilter* VisionFilter::instance = NULL;

VisionFilter *VisionFilter::getInstance()
{
    if(instance == NULL)
        instance = new VisionFilter();
    return instance;
}

VisionFilter::VisionFilter()
{
    // initializing filter objects
    for(int i=0; i<NUM_TEAMS; ++i)
        for(int j=0; j<MAX_ID_NUM; ++j)
            robotFilter[i][j] = new RobotFilter();

    ballFilter = new BallFilter();

    for (int i=0; i<MAX_CAMERA_COUNT; i++)
        cameraLastFrameTime[i] = 0;

    ParameterManager* pm = ParameterManager::getInstance();
//    txtlogFile.open(pm->get<string>("general.debug.ball").c_str());
}

VisionFilter::~VisionFilter()
{
    txtlogFile.close();
}

void VisionFilter::check()
{
    mtx_.lock();

    //    update World Model
    for( int tm = 0 ; tm < NUM_TEAMS; tm++ )   {
        for( int i = 0; i < MAX_ID_NUM; i++ )   {
            robotFilter[tm][i]->run();
//            cout << robotFilter[tm][i]->isOnField() << endl;
            world->updateRobotState( (SSL::Color)tm, i ,
                                     robotFilter[tm][i]->m_filteredPosition ,
                                     robotFilter[tm][i]->m_filteredSpeed,
                                     robotFilter[tm][i]->isOnField());
        }
    }

    ballFilter->run();
    world->updateBallState( 0, ballFilter->m_filteredPosition,
                               ballFilter->m_filteredVelocity,
                               ballFilter->m_acceleration );

    mtx_.unlock();
}

void VisionFilter::update(const SSL_WrapperPacket &packet)
{
    mtx_.lock();
    try {
        if(packet.has_detection())
        {
            if( packet.detection().camera_id() < MAX_CAMERA_COUNT )
            {
                double frame_time = packet.detection().t_capture();
                if( frame_time <=  cameraLastFrameTime[packet.detection().camera_id()] ) {
                    throw "Vision: Decayed packet !!!!" ;
                }
                else
                    cameraLastFrameTime[packet.detection().camera_id()] = frame_time;
            }

            if(ParameterManager::getInstance()->get<bool>("vision.camera_0_filtered"))
                if( packet.detection().camera_id() == 0 )
                    throw "Vision: Camera 0 is filtered out";
            if(ParameterManager::getInstance()->get<bool>("vision.camera_1_filtered"))
                if( packet.detection().camera_id() == 1 )
                    throw "Vision: Camera 1 is filtered out";
            if(ParameterManager::getInstance()->get<bool>("vision.camera_2_filtered"))
                if( packet.detection().camera_id() == 2 )
                    throw "Vision: Camera 2 is filtered out";
            if(ParameterManager::getInstance()->get<bool>("vision.camera_3_filtered"))
                if( packet.detection().camera_id() == 3 )
                    throw "Vision: Camera 3 is filtered out";


            float diff_time = packet.detection().t_sent() - last_frame_time;
            FPS = 1/diff_time;
            last_frame_time = packet.detection().t_sent();

            SSLFrame frame;

            frame.camera_id = packet.detection().camera_id();
            frame.frame_number = packet.detection().frame_number();

    //        temp_frame.setToCurrentTimeMilliSec();
            frame.timeStampMilliSec = packet.detection().t_capture() * 1000.0;

            if(ParameterManager::getInstance()->get<bool>("vision.filter_blue_robots") == false)
                for(int i=0; i < packet.detection().robots_blue_size(); i++)
                {
                    SSL_DetectionRobot Robot = packet.detection().robots_blue(i);
                    frame.position = Vector3D(Robot.x(), Robot.y(), Robot.orientation());
                    frame.confidence = Robot.confidence();
                    robotFilter[SSL::Blue][Robot.robot_id()]->putNewFrame(frame);
                }

            if(ParameterManager::getInstance()->get<bool>("vision.filter_yellow_robots") == false)
                for(int i=0; i< packet.detection().robots_yellow_size(); i++)
                {
                    SSL_DetectionRobot Robot = packet.detection().robots_yellow(i);
                    frame.position = Vector3D(Robot.x(), Robot.y(), Robot.orientation());
                    frame.confidence = Robot.confidence();
                    robotFilter[SSL::Yellow][Robot.robot_id()]->putNewFrame(frame);
                }

            vector<SSLFrame> balls_vec;
            for(int i=0; i< packet.detection().balls_size(); i++)
            {
                SSL_DetectionBall Ball = packet.detection().balls(i);
                frame.position = Vector2D(Ball.x(), Ball.y()).to3D();
                frame.confidence = Ball.confidence();
                balls_vec.push_back(frame);

            //  file <<i << " , " << (long)temp_frame.timeStampMilliSec<< " , ";
            //  file << Ball.x() <<" , " << Ball.y() << endl;
            }

            if(balls_vec.empty()) {
                throw "Warning:: No ball exists in current frame";
            }
            if(ballFilter->isEmpty()) {
                ballFilter->initialize(balls_vec[0]);
                throw "Initializing ball filter module";
            }
            if(balls_vec.size() == 1) {
                ballFilter->putNewFrame(balls_vec[0]);
            }
            else {
                ballFilter->putNewFrameWithManyBalls(balls_vec);
                throw "Warning:: More than One ball exist in current frame" ;
            }
        }

        if(packet.has_geometry())   {
            // SSL_GeometryData geometryData = packet.geometry();
        }

    }
    catch (const char* msg) {
//        cout << msg << endl;
    }
    mtx_.unlock();
}
