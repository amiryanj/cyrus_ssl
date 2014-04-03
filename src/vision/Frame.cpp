#include "Frame.h"

Frame::Frame()
{
    this->setToCurrentTimeMilliSec();
}

// default constructor
Frame::Frame(const Vector3D &pose, const double &time, double conf)
{
    this->set(pose, time, conf);
}

void Frame::set(const Vector3D &pose, const double &time, double conf)
{
    this->position = pose;
    this->confidence = conf;

    if(time == -1)
        setToCurrentTimeMilliSec();
    else
        this->timeStampMilliSec = time;
}

void Frame::setToCurrentTimeMilliSec()
{
    ptime t(microsec_clock::universal_time());   
    time_duration td = t.time_of_day();
    timeStampMilliSec =  td.total_microseconds()/1000.0;
}
