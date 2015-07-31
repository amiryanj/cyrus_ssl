#ifndef _ROBOTKALMANFILTER_H
#define _ROBOTKALMANFILTER_H

#include "kalmanfilter.h"
#include "sslframe.h"
#include <vector>
#include "paramater-manager/parametermanager.h"

class RobotKalmanFilter
{
    friend class VisionFilter;
    friend class MainWindow;
public:
    RobotKalmanFilter();

    void putNewFrame(OneObjectFrame &fr);
    bool isEmpty() const;
    bool isOnField() const;

    // main method for updating state vectors
    void run();
    Vector3D m_filteredPosition;
    Vector3D m_filteredVelocity;

    Vector3D m_rawPosition;
    Vector3D m_rawVelocity;

    bool hasUnprocessedData;

protected:
    KalmanFilter KF;
    std::vector<OneObjectFrame> rawData;
    double last_time_msec;
    double last_dt_msec;
};

#endif // ROBOTKALMANFILTER_H
