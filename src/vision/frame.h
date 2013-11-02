#ifndef FRAME_H
#define FRAME_H

#include "../general.h"
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace boost::posix_time;

struct frame
{
    frame(const Vector3D &pose, const double &time = -1 );
    frame();
    double timeTag; // unit = second
    Vector3D position;

    void setToCurrentTime();

//    ptime *t;



};

#endif // FRAME_H
