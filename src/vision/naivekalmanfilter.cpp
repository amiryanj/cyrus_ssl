#include "naivekalmanfilter.h"

NaiveKalmanFilter::NaiveKalmanFilter()
{
    Identity.setIdentity();
    x.setZero();
    F.setIdentity();
    H.setIdentity();
    P.setIdentity(); // initialize covarince matrix
    P(0, 0) = P(1, 1) = pow(40, 2);
    P(2, 2) = pow(.1, 2);
    P(3, 3) = P(4, 4) = pow(80, 2);
    P(5, 5) = pow(.2, 2);

    R.setIdentity();
    R(0, 0) = R(1, 1) = pow(40, 2);
    R(2, 2) = pow(.1, 2);
    R(3, 3) = R(4, 4) = pow(80, 2);
    R(5, 5) = pow(.2, 2);

    Q.setIdentity();
    Q(0, 0) = Q(1, 1) = pow(10, 2);
    Q(2, 2) = pow(.05, 2);
    Q(3, 3) = Q(4, 4) = pow(20, 2);
    Q(5, 5) = pow(.1, 2);
}

void NaiveKalmanFilter::predict(double delta_t_sec)
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

KalmanVector NaiveKalmanFilter::getPredict(double delta_t_sec)
{
    F(0, 3) = delta_t_sec;
    F(1, 4) = delta_t_sec;
    F(2, 5) = delta_t_sec;

    return (F * x);
}

void NaiveKalmanFilter::update(KalmanVector z)
{
    KalmanVector y = z - H * x;
    KalmanMatrix S = H * P * H.transpose() + R;
    KalmanMatrix K = P * H.transpose() * S.inverse();
//    K = K * 0.4;
    x = x + K * y;
    P = (Identity - K * H) * P;
}
