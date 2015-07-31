#ifndef _ONEOBJECTFRAME_H
#define _ONEOBJECTFRAME_H

#include "../../shared/utility/vector3d.h"

const static int CAMERA_FPS = 20;

struct OneObjectFrame
{
    OneObjectFrame();
    OneObjectFrame(const Vector3D &pose, const double &time = -1, double conf = 0);
    void set(const Vector3D &pose, const double &time = -1, double conf = 0);

    Vector3D position;
    Vector3D velocity;
    Vector3D acceleration;

    double timeStampMSec; // unit = second
    double confidence;
    short camera_id;
    long frame_number;

    void setToCurrentTimeMilliSec();

    OneObjectFrame& operator =(const OneObjectFrame &other);

};

#endif // FRAME_H
