#ifndef _FRAME_H
#define _FRAME_H

#include "../../shared/utility/vector3d.h"

const static int CAMERA_FPS = 20;

struct SSLFrame
{
    SSLFrame();
    SSLFrame(const Vector3D &pose, const double &time = -1, double conf = 0);
    void set(const Vector3D &pose, const double &time = -1, double conf = 0);

    Vector3D position;
    double timeStampMilliSec; // unit = second
    double confidence;
    short camera_id;
    long frame_number;

    void setToCurrentTimeMilliSec();

    SSLFrame& operator =(const SSLFrame &other);

};

#endif // FRAME_H
