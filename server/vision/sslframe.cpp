#include "sslframe.h"
#include "../../shared/utility/generalmath.h"

OneObjectFrame::OneObjectFrame()
{
}

// default constructor
OneObjectFrame::OneObjectFrame(const Vector3D &pose, const double &time, double conf)
{
    this->set(pose, time, conf);
}

void OneObjectFrame::set(const Vector3D &pose, const double &time, double conf)
{
    this->position = pose;
    this->confidence = conf;

    if(time == -1)
        setToCurrentTimeMilliSec();
    else
        this->timeStampMSec = time;
}

void OneObjectFrame::setToCurrentTimeMilliSec()
{
    timeStampMSec = currentTimeMSec();
}

OneObjectFrame &OneObjectFrame::operator =(const OneObjectFrame &other)
{
    this->timeStampMSec = other.timeStampMSec;
    this->camera_id = other.camera_id;
    this->confidence = other.confidence;
    this->position = other.position;
    this->velocity = other.velocity;

    return (*this);
}
