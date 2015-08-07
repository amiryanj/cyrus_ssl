#ifndef _ROBOTKALMANFILTER_H
#define _ROBOTKALMANFILTER_H

#include "robotfilter.h"
#include "kalmanfilter.h"

class RobotKalmanFilter : RobotFilter
{
    friend class VisionFilter;
    friend class MainWindow;
public:
    RobotKalmanFilter();

    // main method for updating state vectors
    bool run();
protected:
    KalmanFilter KF;
};

#endif // ROBOTKALMANFILTER_H
