#ifndef FRAME_H
#define FRAME_H

#include "../general.h"
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace boost::posix_time;

struct frame
{
    frame();
    frame(const Vector3D &pose, const double &time = -1 , double conf = 0);
    void set(const Vector3D &pose, const double &time = -1, double conf = 0);
    double timeTag; // unit = second
    double confidence;
    Vector3D position;

    void setToCurrentTime();

//    ptime *t;



};

#endif // FRAME_H
