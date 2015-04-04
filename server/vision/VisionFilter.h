#ifndef _VISIONFILTER_H
#define _VISIONFILTER_H

#include <fstream>
#include <boost/signals2/mutex.hpp>
#include "../../common/general.h"
#include "../ai/SSLWorldModel.h"
#include "../../common/tools/SSLListener.h"
#include "../../common/protoc/vision/cpp/messages_robocup_ssl_wrapper.pb.h"
#include "../../common/protoc/vision/cpp/messages_robocup_ssl_detection.pb.h"
#include "RobotFilter.h"
#include "BallFilter.h"
#include "NaiveKalman.h"

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

    BallFilter *ballFilter;
private:
    RobotFilter *robotFilter[NUM_TEAMS][MAX_ID_NUM];
    double cameraLastFrameTime[MAX_CAMERA_COUNT];
    std::ofstream txtlogFile;

    float last_frame_time;
    float FPS;

    boost::signals2::mutex mtx_;

};

#endif // _VISIONFILTER_H
