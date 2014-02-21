#include "frame.h"

frame::frame()
{
    this->setToCurrentTimeMilliSec();
}

// default constructor
frame::frame(const Vector3D &pose, const double &time, double conf)
{
    this->set(pose, time, conf);
}

void frame::set(const Vector3D &pose, const double &time, double conf)
{
    this->position = pose;
    this->confidence = conf;

    if(time == -1)
        setToCurrentTimeMilliSec();
    else
        this->timeStampMilliSec = time;
}

void frame::setToCurrentTimeMilliSec()
{
    ptime t(microsec_clock::universal_time());   
    time_duration td = t.time_of_day();
    timeStampMilliSec =  td.total_microseconds()/1000.0;
}
