#ifndef KALMANFILTER_H
#define KALMANFILTER_H

#include "../../shared/tools/kalman-cpp/kalman.hpp"
#include "../../shared/utility/vector3d.h"
#include <iostream>

class KalmanFilter
{
public:
    KalmanFilter();

    Kalman *k;

    void init();
    void update(const Vector3D &measured_pos, const Vector3D &measured_vel, double dt_sec);

    Vector3D getFilteredPosition() const;
    Vector3D getFilteredVelocity() const;
};

#endif // KALMANFILTER_H
