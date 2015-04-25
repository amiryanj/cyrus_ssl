#include "sslframe.h"
#include "../../shared/utility/generalmath.h"

SSLFrame::SSLFrame()
{
}

// default constructor
SSLFrame::SSLFrame(const Vector3D &pose, const double &time, double conf)
{
    this->set(pose, time, conf);
}

void SSLFrame::set(const Vector3D &pose, const double &time, double conf)
{
    this->position = pose;
    this->confidence = conf;

    if(time == -1)
        setToCurrentTimeMilliSec();
    else
        this->timeStampMilliSec = time;
}

void SSLFrame::setToCurrentTimeMilliSec()
{
    timeStampMilliSec = currentTimeMSec();
}

SSLFrame &SSLFrame::operator =(const SSLFrame &other)
{
    this->timeStampMilliSec = other.timeStampMilliSec;
    this->camera_id = other.camera_id;
    this->confidence = other.confidence;
    this->position = other.position;

    return (*this);
}
