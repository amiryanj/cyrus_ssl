#include "RobotFilter.h"
#include "tools/sslmath.h"

using namespace std;

#define EPS 1e-5

RobotFilter::RobotFilter()
{    
    last_update_time_msec = 0;

    rawPositionList.reserve(MAX_RAW_DATA_MEMORY + 1);
    // rawSpeedList is set to zero by default
    __medianFilterIndex = 0;

}

// insert new frame in the list and remove expired frames
void RobotFilter::putNewFrame(const Frame &fr)
{
    rawPositionList.insert(rawPositionList.begin(), fr);
//    std::cout << "Robot Confidence = " <<fr.confidence << std::endl;
    if(rawPositionList.size() > MAX_RAW_DATA_MEMORY)
        rawPositionList.pop_back();
    last_delta_t_sec = (fr.timeStampMilliSec - last_update_time_msec)/ 1000.0;
    last_update_time_msec = fr.timeStampMilliSec;

    Vector3D currentSpeed_;
    if (rawPositionList.size() >= ROBOT_SPEED_LIMIT_FILTER) {
        currentSpeed_ = (rawPositionList[0].position - rawPositionList[ROBOT_SPEED_LIMIT_FILTER].position)
                / (rawPositionList[0].timeStampMilliSec - rawPositionList[ROBOT_SPEED_LIMIT_FILTER].timeStampMilliSec);
    }
    else {
        currentSpeed_ = (rawPositionList[0].position - rawPositionList.back().position)
                / (rawPositionList[0].timeStampMilliSec - rawPositionList.back().timeStampMilliSec);
    }

    rawSpeedList[__medianFilterIndex++] = currentSpeed_;
    if (__medianFilterIndex >= MAX_ROBOT_MEDIAN_MEMORY)
        __medianFilterIndex = 0;
}

bool RobotFilter::isEmpty()
{
    return rawPositionList.empty();
}

bool RobotFilter::isOnField()
{
    return (rawPositionList.size() >= 7);
}

void RobotFilter::runFilter()
{
    // remove decayed frames
    Frame fake_frame;
    fake_frame.setToCurrentTimeMilliSec();
    while(!rawPositionList.empty())
    {
        Frame listed_fr = rawPositionList.back();
        if((fake_frame.timeStampMilliSec - listed_fr.timeStampMilliSec) > ((2 * MAX_RAW_DATA_MEMORY)/(CAMERA_FPS/1000.0)))
            rawPositionList.pop_back();
        else
            break;
    }

    if( rawPositionList.size() == 0 )
        return;

    //.first is length, second is index
    pair<float, int> medianFilterValues[MAX_ROBOT_MEDIAN_MEMORY];
    for (int i = 0; i < MAX_ROBOT_MEDIAN_MEMORY; i++)
        medianFilterValues[i] = make_pair(rawSpeedList[i].lenght2D(), i);

    sort(medianFilterValues, medianFilterValues + MAX_ROBOT_MEDIAN_MEMORY);
    int medianFilteredSpeed_Index = medianFilterValues[MAX_ROBOT_MEDIAN_MEMORY/2].second;
    m_medianFilteredSpeed = rawSpeedList[medianFilteredSpeed_Index];


    Frame last_frame = rawPositionList.front();
    /*  farzad's prediction */
    /*
    if (rawPositionList.size() >= 2) {
        last_frame = rawPositionList[1];
        last_frame.position += Vector3D(m_medianFilteredSpeed * last_delta_t_sec, 0.0);
    }
    */
    /* javad's prediction */

    for (int i = 0 ; i < MAX_ROBOT_MEDIAN_MEMORY && i+1 < rawPositionList.size(); i++)
        if (fabs(((rawPositionList[i].position - rawPositionList[i+1].position)
                  / (rawPositionList[i].timeStampMilliSec - rawPositionList[i+1].timeStampMilliSec)).lenght2D()
                - m_medianFilteredSpeed.lenght2D()) <= EPS)
        {
            last_frame.position =
                    rawPositionList[i+1].position +
                        (rawPositionList[i].position - rawPositionList[i+1].position)
                        * (i+1);
            break;
        }

    Vector3D last_observe = last_frame.position;

    naiveFilter.predict(last_delta_t_sec);
    naiveFilter.observe(last_observe, last_delta_t_sec);
    FilterState fs = naiveFilter.filter();
    this->m_filteredPosition = fs.pos;
    this->m_filteredSpeed = fs.vel * 10;

//    naiveFilter.x(2, 0) = continuousRadian(naiveFilter.x(2), -M_PI);

}

Vector3D RobotFilter::getFilteredPosition() const
{
    return m_filteredPosition;
}

Vector3D RobotFilter::getFilteredSpeed() const
{
    return m_filteredSpeed;
}

