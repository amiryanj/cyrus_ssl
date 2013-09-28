#include "SSLRobotKalmanFilter.h"

SSLRobotKalmanFilter::SSLRobotKalmanFilter()
{    
    Vector3D p_;
    filteredPosition = p_;
    filteredSpeed = p_;

    setDim(6, 1, 3, 3, 3);

//    runFilter();

}

void SSLRobotKalmanFilter::setNewFrame(const frame &fr)
{
    rawPositionList.push_front(fr);
    if(rawPositionList.size() > MAX_RAW_DATA_MEMORY)
        rawPositionList.pop_back();

}

bool SSLRobotKalmanFilter::isEmpty()
{
    return rawPositionList.empty();
}

bool SSLRobotKalmanFilter::isOnField()
{
    return (rawPositionList.size() >= 6);
}

void SSLRobotKalmanFilter::runFilter()
{
    if( rawPositionList.size() == 0 )
        return;

    frame last_frame = rawPositionList.front();
    Vector3D lastPosition = last_frame.position; // point3D

    if( rawPositionList.size() == 1 )
    {
        Vector init_state(6);
        init_state(1) = lastPosition.x;
        init_state(2) = lastPosition.y;
        init_state(3) = lastPosition.teta;

        Matrix init_cov(6, 6);
        for(int i=1; i <= 6; i++)
        {
            init_cov(i, i) = 0.01;
        }

        this->init(init_state, init_cov);
        return;
    }

    if( rawPositionList.size() >= 2 )
    {
        Vector obs_pose(3);
        obs_pose(1) = lastPosition.x;
        obs_pose(2) = lastPosition.y;
        obs_pose(3) = lastPosition.teta;
//        step(, lastPosition);
    }
}

void SSLRobotKalmanFilter::makeA()
{
}

void SSLRobotKalmanFilter::makeH()
{
}

void SSLRobotKalmanFilter::makeV()
{
}

void SSLRobotKalmanFilter::makeR()
{
}

void SSLRobotKalmanFilter::makeW()
{
}

void SSLRobotKalmanFilter::makeQ()
{
}

void SSLRobotKalmanFilter::makeProcess()
{
}

void SSLRobotKalmanFilter::makeMeasure()
{
}
