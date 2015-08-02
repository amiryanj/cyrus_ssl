#ifndef _VISIONFILTER_H
#define _VISIONFILTER_H

#include <fstream>
#include <boost/signals2/mutex.hpp>
#include "../../shared/general.h"
#include "../ai/SSLWorldModel.h"
#include "../../shared/tools/ssllistener.h"
#include "../../shared/proto/vision/cpp/messages_robocup_ssl_wrapper.pb.h"
#include "../../shared/proto/vision/cpp/messages_robocup_ssl_detection.pb.h"
#include "robotclusterfilter.h"
#include "ballfilter.h"
#include "robotkalmanfilter.h"
#include <QMutex>


const static int MAX_CAMERA_COUNT = 4;

class VisionFilter : public SSLListener
{
    friend class MainWindow;
    VisionFilter();
    ~VisionFilter();
    static VisionFilter* instance;

public:
    static VisionFilter* getInstance();
    void check();
    void update(const SSL_WrapperPacket &packet);


    //temp test function
    Vector3D getUnderTestRobotFilteredVelocity();
    Vector3D getUnderTestRobotFilteredPosition();

    Vector3D getUnderTestRobotRawVelocity();
    Vector3D getUnderTestRobotRawPosition();


    BallFilter *ballFilter;
private:
    RobotClusterFilter *robotFilter_cluster[NUM_TEAMS][MAX_ID_NUM];
    double cameraLastFrameTime[MAX_CAMERA_COUNT];

    RobotKalmanFilter *robotFilter_kalman[NUM_TEAMS][MAX_ID_NUM];

    float last_frame_time;
    float FPS;

    QMutex mtx_;

};

#endif // _VISIONFILTER_H
