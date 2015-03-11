#ifndef FRAME_H
#define FRAME_H

#include "../../common/general.h"
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace boost::posix_time;

const static int CAMERA_FPS = 20;

struct Frame
{
    Frame();
    Frame(const Vector3D &pose, const double &time = -1 , double conf = 0);
    void set(const Vector3D &pose, const double &time = -1, double conf = 0);
    double timeStampMilliSec; // unit = second
    double confidence;
    Vector3D position;
    short camera_id;

    void setToCurrentTimeMilliSec();

    Frame& operator =(const Frame &other);
//    ptime *t;



};

#endif // FRAME_H
