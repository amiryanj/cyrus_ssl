#include "RobotFilter.h"
#include "../../common/math/sslmath.h"

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
void RobotFilter::putNewFrame(const SSLFrame &fr)
{
    last_update_time_msec = SSL::currentTimeMSec();
    rawPositionList.insert(rawPositionList.begin(), fr);
//    std::cout << "Robot Confidence = " <<fr.confidence << std::endl;
    if(rawPositionList.size() > MAX_RAW_DATA_MEMORY)
        rawPositionList.pop_back();    

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
    return (rawPositionList.size() >= 5);
}

void RobotFilter::run()
{
    // removing decayed frames
    if((SSL::currentTimeMSec() - last_update_time_msec) > 10000)
        rawPositionList.clear();

    if( rawPositionList.size() < 2 )
        return;

    //first is length, second is index
    pair<float, int> medianFilterValues[MAX_ROBOT_MEDIAN_MEMORY];
    for (int i = 0; i < MAX_ROBOT_MEDIAN_MEMORY; i++)
        medianFilterValues[i] = make_pair(rawSpeedList[i].lenght2D(), i);

    sort(medianFilterValues, medianFilterValues + MAX_ROBOT_MEDIAN_MEMORY);
    int medianFilteredSpeed_Index = medianFilterValues[MAX_ROBOT_MEDIAN_MEMORY/2].second;
    m_medianFilteredSpeed = rawSpeedList[medianFilteredSpeed_Index];


    SSLFrame last_frame = rawPositionList.front();
    /* javad's prediction */

    for (uint i = 0 ; i < MAX_ROBOT_MEDIAN_MEMORY && i+1 < rawPositionList.size(); i++)
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

    alphaBetaFilter.predict(last_frame.timeStampMilliSec / 1000.0
                           - rawPositionList[1].timeStampMilliSec / 1000.0);
    alphaBetaFilter.observe(last_observe, m_medianFilteredSpeed, Vector3D(0.0, 0.0, 0.0));
    SSLObjectState fs = alphaBetaFilter.filter();
    this->m_filteredPosition = fs.pos;
    this->m_filteredSpeed = fs.vel * 10;

//    naiveFilter.x(2, 0) = continuousRadian(naiveFilter.x(2), -M_PI);

}

