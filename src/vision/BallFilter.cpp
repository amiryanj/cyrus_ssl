#include "BallFilter.h"

#include "../ai/SSLWorldModel.h"
#include "../definition/SSLRobot.h"

BallFilter::BallFilter()
{
    last_update_time_msec = 0;

    rawPositionList.reserve(MAX_BALL_MEMORY + 1);
}

void BallFilter::putNewFrame(const Frame &fr)
{
    rawPositionList.insert(rawPositionList.begin(), fr);
//    std::cout << "Robot Confidence = " <<fr.confidence << std::endl;
    if(rawPositionList.size() > MAX_BALL_MEMORY)
        rawPositionList.pop_back();
    last_delta_t_sec = (fr.timeStampMilliSec - last_update_time_msec)/ 1000.0;
    last_update_time_msec = fr.timeStampMilliSec;

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

    Frame last_frame = rawPositionList.front();
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
        naiveFilter.m_alfa = 0.3;
        naiveFilter.m_beta = 0.2;
    }
    else {
        naiveFilter.m_alfa = 0.1;
        naiveFilter.m_beta = 0.05;
    }

    FilterState fs = naiveFilter.filter();
    this->m_filteredPosition = fs.pos.to2D();
    this->m_filteredSpeed = fs.vel.to2D();
}

Vector2D BallFilter::getFilteredSpeed() const
{
    return m_filteredSpeed;
}

Vector2D BallFilter::getFilteredPosition() const
{
    return m_filteredPosition;
}
