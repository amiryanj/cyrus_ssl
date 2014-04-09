#include "BallFilter.h"

#include "../ai/SSLWorldModel.h"
#include "../definition/SSLRobot.h"

#define EPS 1e-5

BallFilter::BallFilter()
{
    last_update_time_msec = 0;

    rawPositionList.reserve(MAX_BALL_MEMORY + 1);
    // rawSpeedList is set to zero by default
    __medianFilterIndex = 0;
}

void BallFilter::putNewFrame(const Frame &fr)
{
    rawPositionList.insert(rawPositionList.begin(), fr);
//    std::cout << "Robot Confidence = " <<fr.confidence << std::endl;
    if(rawPositionList.size() > MAX_BALL_MEMORY)
        rawPositionList.pop_back();

    last_delta_t_sec = (fr.timeStampMilliSec - last_update_time_msec)/ 1000.0;
    last_update_time_msec = fr.timeStampMilliSec;

    Vector2D currentSpeed_;
    if (rawPositionList.size() >= BALL_SPEED_LIMIT_FILTER)
        currentSpeed_ = (rawPositionList[0].position.to2D() - rawPositionList[BALL_SPEED_LIMIT_FILTER].position.to2D())
                / (rawPositionList[0].timeStampMilliSec - rawPositionList[BALL_SPEED_LIMIT_FILTER].timeStampMilliSec);
    else
        currentSpeed_ = (rawPositionList[0].position.to2D() - rawPositionList.back().position.to2D())
                / (rawPositionList[0].timeStampMilliSec - rawPositionList.back().timeStampMilliSec);

    rawSpeedList[__medianFilterIndex++] = currentSpeed_;
    if (__medianFilterIndex >= MAX_BALL_MEDIAN_MEMORY)
        __medianFilterIndex = 0;

}

void BallFilter::runFilter()
{
    // remove decayed frames
    Frame fake_frame;
    fake_frame.setToCurrentTimeMilliSec();
    while(!rawPositionList.empty())
    {
        Frame listed_fr = rawPositionList.back();
        if((fake_frame.timeStampMilliSec - listed_fr.timeStampMilliSec) > ((2 * MAX_BALL_MEMORY)/(CAMERA_FPS/1000.0)))
            rawPositionList.pop_back();
        else
            break;
    }

    if( rawPositionList.size() == 0 )
        return;

    //.first is length, second is index
    pair<float, int> medianFilterValues[MAX_BALL_MEDIAN_MEMORY];
    for (int i = 0; i < MAX_BALL_MEDIAN_MEMORY; i++)
        medianFilterValues[i] = make_pair(rawSpeedList[i].lenght(), i);

    sort(medianFilterValues, medianFilterValues + MAX_BALL_MEDIAN_MEMORY);
    int medianFilteredSpeed_Index = medianFilterValues[MAX_BALL_MEDIAN_MEMORY/2].second;
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

    for (int i = 0 ; i < MAX_BALL_MEDIAN_MEMORY && i+1 < rawPositionList.size(); i++)
        if (fabs(((rawPositionList[i].position.to2D() - rawPositionList[i+1].position.to2D())
                  / (rawPositionList[i].timeStampMilliSec - rawPositionList[i+1].timeStampMilliSec)).lenght()
                - m_medianFilteredSpeed.lenght()) <= EPS)
        {
            last_frame.position =
                    rawPositionList[i+1].position + Vector3D(
                        (rawPositionList[i].position.to2D() - rawPositionList[i+1].position.to2D())
                        * (i+1), 0.0
                        );
            break;
        }


    Vector3D last_observe = last_frame.position;

    naiveFilter.predict(last_delta_t_sec);
    naiveFilter.observe(last_observe, last_delta_t_sec);

    vector<SSLRobot*> all_robots = world->all_inFields();
    bool near_robots = false;
    for(int i=0; i<all_robots.size(); i++) {
        SSLRobot* robot = all_robots[i];
        if((last_frame.position.to2D() - robot->Position().to2D()).lenght() < (ROBOT_RADIUS + BALL_RADIUS)* 1.1 ) {
            near_robots = true;
            break;
        }
    }
    if(near_robots) {
        naiveFilter.m_alfa = 0.2;
        naiveFilter.m_beta = 0.13;
    }
    else {
        naiveFilter.m_alfa = 0.1;
        naiveFilter.m_beta = 0.03;
    }

    FilterState fs = naiveFilter.filter();    
    this->m_filteredPosition = fs.pos.to2D();
    this->m_unfilteredSpeed = fs.vel.to2D();
}

Vector2D BallFilter::getUnfilteredSpeed() const
{
    return m_unfilteredSpeed;
}

Vector2D BallFilter::getMedianFilteredSpeed() const
{
    return m_medianFilteredSpeed;
}

Vector2D BallFilter::getFilteredPosition() const
{
    return m_filteredPosition;
}
