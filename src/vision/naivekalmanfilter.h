#ifndef NAIVEKALMANFILTER_H
#define NAIVEKALMANFILTER_H

#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/LU>
#include <eigen3/Eigen/Eigen>
using namespace Eigen;

class NaiveKalmanFilter
{
public:
    typedef Matrix<double, 6, 1>     KalmanVector;
    typedef Matrix<double, 6, 6>     KalmanMatrix;

    NaiveKalmanFilter();
    void predict();
    void update(KalmanVector z);

    KalmanMatrix  F;  // state transition model
    KalmanMatrix  Q;  // Covariance of process noise
    KalmanMatrix  P;  //
    KalmanMatrix  R;  // Covariance of observation noise
    KalmanVector  x;  // state vector
//    KalmanMatrix  B;  // Control Input Model
//    KalmanMatrix  u;

    KalmanMatrix  H; // Observation Model
    KalmanMatrix  Identity; // Identity Matrix :))))))

    double delta_t_sec;
private:

    Vector3d test_vec;
};

#endif // NAIVEKALMANFILTER_H
