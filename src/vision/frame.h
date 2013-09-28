#ifndef FRAME_H
#define FRAME_H
#include "tools/vector3d.h"
#include "iostream"
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace boost::posix_time;

struct frame
{
    frame(const Vector3D &pose, const double &time = -1 );
    frame();
    double timeTag;
    Vector3D position;

    void setToCurrentTime();

//    ptime *t;



};

#endif // FRAME_H
