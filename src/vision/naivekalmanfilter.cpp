#include "naivekalmanfilter.h"

NaiveKalmanFilter::NaiveKalmanFilter()
{
    Identity.setIdentity();
    x.setZero();
    F.setIdentity();
    H.setIdentity();
    P.setIdentity(); // initialize covarince matrix
    P = P * pow(1000, 2);
    R.setIdentity();
    R = R * 10000;
    Q.setIdentity();
    Q = Q * 10000;
}

void NaiveKalmanFilter::predict()
{
    // update F
    F(0, 3) = delta_t_sec;
    F(1, 4) = delta_t_sec;
    F(2, 5) = delta_t_sec;

    // update U
    // **************
    x = F * x;
    P = F * P * F.transpose() + Q;
}

void NaiveKalmanFilter::update(KalmanVector z)
{
    KalmanVector y = z - H * x;
    KalmanMatrix S = H * P * H.transpose() + R;
    KalmanMatrix K = P * H.transpose() * S.inverse();
    K = K * 0.05;
    x = x + K * y;
    P = (Identity - K * H) * P;
}
