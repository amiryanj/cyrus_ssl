#ifndef SSLROBOTKALMANFILTER_H
#define SSLROBOTKALMANFILTER_H

#include "../tools/vector3d.h"
#include "naivekalmanfilter.h"
#include "frame.h"

#define MAX_RAW_DATA_MEMORY 30

class SSLRobotKalmanFilter //: public Kalman::EKFilter<double, 1>
{
public:
    SSLRobotKalmanFilter();
    void putNewFrame(const frame &fr);
    bool isEmpty();
    bool isOnField();

    // main method for updating state vectors
    void runFilter();

    Vector3D getFilteredSpeed() const;
    Vector3D getFilteredPosition() const;

private:
    std::vector<frame> rawPositionList;
    double last_update_time_msec;
    double last_delta_t_sec;

    Vector3D filteredPosition;
    Vector3D filteredSpeed;

    NaiveKalmanFilter naiveFilter;

};

#endif // SSLROBOTKALMANFILTER_H
