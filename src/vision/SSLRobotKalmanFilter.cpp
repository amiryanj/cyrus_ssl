#include "SSLRobotKalmanFilter.h"
#include "tools/sslmath.h"

using namespace std;

SSLRobotKalmanFilter::SSLRobotKalmanFilter()
{    
    last_update_time_msec = 0;

    rawPositionList.reserve(MAX_RAW_DATA_MEMORY + 1);

}

// insert new frame in the list and remove expired frames
void SSLRobotKalmanFilter::putNewFrame(const frame &fr)
{
    rawPositionList.insert(rawPositionList.begin(), fr);
//    std::cout << "Robot Confidence = " <<fr.confidence << std::endl;
    if(rawPositionList.size() > MAX_RAW_DATA_MEMORY)
        rawPositionList.pop_back();
    last_delta_t_sec = (fr.timeStampMilliSec - last_update_time_msec)/ 1000.0;
    last_update_time_msec = fr.timeStampMilliSec;
}

bool SSLRobotKalmanFilter::isEmpty()
{
    return rawPositionList.empty();
}

bool SSLRobotKalmanFilter::isOnField()
{
    return (rawPositionList.size() >= 4);
}

void SSLRobotKalmanFilter::runFilter()
{
    // remove decayed frames
    frame fake_frame;
    fake_frame.setToCurrentTimeMilliSec();
    while(!rawPositionList.empty())
    {
        frame listed_fr = rawPositionList.back();
        if((fake_frame.timeStampMilliSec - listed_fr.timeStampMilliSec) > ((2 * MAX_RAW_DATA_MEMORY)/(CAMERA_FPS/1000.0)))
            rawPositionList.pop_back();
        else
            break;
    }

    if( rawPositionList.size() == 0 )
        return;

    frame last_frame = rawPositionList.front();
    Vector3D last_observe = last_frame.position;

    naiveFilter.predict(last_delta_t_sec);
    naiveFilter.observe(last_observe, last_delta_t_sec);
    FilterState fs = naiveFilter.filter();
    this->m_filteredPosition = fs.pos;
    this->m_filteredSpeed = fs.vel;

//    naiveFilter.x(2, 0) = continuousRadian(naiveFilter.x(2), -M_PI);

}

Vector3D SSLRobotKalmanFilter::getFilteredPosition() const
{
    return m_filteredPosition;
}

Vector3D SSLRobotKalmanFilter::getFilteredSpeed() const
{
    return m_filteredSpeed;
}

