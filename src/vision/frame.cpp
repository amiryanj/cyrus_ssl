#include "frame.h"

frame::frame()
{
    this->setToCurrentTime();
}

// default constructor
frame::frame(const Vector3D &pose, const double &time)
{
    this->position = pose;

    if(time == -1)
        setToCurrentTime();
    else
        this->timeTag = time;
}

void frame::setToCurrentTime()
{
    ptime t(microsec_clock::universal_time());
    time_duration td = t.time_of_day();
    timeTag =  td.total_microseconds()/1000000.0;
}
