#include "kalmanfilter.h"
#include <iostream>

using namespace std;

KalmanFilter::KalmanFilter()
{
    static const int n = 6; // Number of states
    static const int m = 6; // Number of measurements

    double dt = 1.0/30; // Time step

    Eigen::MatrixXd A(n, n); // System dynamics matrix // transition matrix
    A.setIdentity();
    for(int i=0; i<n/2; i++) {
        A(i, n/2+i) = dt;
    }

//    A <<    1,     0,      0,     dt,       0,      0,
//            0,     1,      0,     0,       dt,      0,
//            0,     0,      1,     0,       0,      dt,
//
//            0,     0,      0,     1,       0,      0,
//            0,     0,      0,     0,       1,      0,
//            0,     0,      0,     0,       0,      1;


    const float q_sigma = 5.0 ;
    Eigen::MatrixXd Q(n, n); // Process noise covariance
    Q <<
         // variance of position data
            q_sigma,0,      0,      0,      0,      0,
            0,      q_sigma,0,      0,      0,      0,
            0,      q_sigma,0.05,   0,      0,      0,
        // variance of velocity data
            0,      0,      0,      q_sigma,0,      0,
            0,      0,      0,      0,      q_sigma,0,
            0,      0,      0,      0,      0,      q_sigma;

    Eigen::MatrixXd H(m, n); // Observation matrix
    H.setIdentity();

    const float r_sigma = 5.0 ;
    Eigen::MatrixXd R(m, m); // Measurement noise covariance
    R <<
         // variance of position data
            r_sigma,0,      0,      0,      0,      0,
            0,      r_sigma,0,      0,      0,      0,
            0,      0,      r_sigma,0,      0,      0,
        // variance of velocity data
            0,      0,      0,      r_sigma,0,      0,
            0,      0,      0,      0,      r_sigma,0,
            0,      0,      0,      0,      0,      r_sigma;

    const float p_sigma = 5.0 ;
    Eigen::MatrixXd P(n, n); // Estimate error covariance
    // Reasonable covariance matrices
    P <<
         // variance of position data
            1,      0,      0,      0,      0,      0,
            0,      1,      0,      0,      0,      0,
            0,      0,      1,      0,      0,      0,
        // variance of velocity data
            0,      0,      0,      1,      0,      0,
            0,      0,      0,      0,      1,      0,
            0,      0,      0,      0,      0,      1  ;


//    std::cout << "A: \n" << A << std::endl;
//    std::cout << "H: \n" << H << std::endl;
//    std::cout << "Q: \n" << Q << std::endl;
//    std::cout << "R: \n" << R << std::endl;
//    std::cout << "P: \n" << P << std::endl;

    k = new Kalman(dt, A, H, Q, R, P);
}

void KalmanFilter::init()
{
    k->init();
}

void KalmanFilter::update(const Vector3D &measured_pos, const Vector3D &measured_vel, double dt_sec)
{
    static const int n = 6;
    double measured_array[n] = {   measured_pos.X(), measured_pos.Y(), measured_pos.Teta(),
                                   measured_vel.X(), measured_vel.Y(), measured_vel.Teta() };
    Eigen::VectorXd y_vec(n);
    for(int i=0; i<n; i++) {
//        y_vec << 1.0f;
        y_vec[i] = measured_array[i];
    }

    Eigen::MatrixXd A(n, n); // System dynamics matrix // transition matrix
    A.setIdentity();
    for(int i=0; i<n/2; i++) {
        A(i, n/2+i) = dt_sec;
    }
//    cout << A << endl;
    k->update(y_vec, dt_sec, A);
}

Vector3D KalmanFilter::getFilteredPosition() const
{
    Eigen::VectorXd fp_ = k->state();
    Vector3D res(fp_[0], fp_[1], fp_[2]);
    return res;
}

Vector3D KalmanFilter::getFilteredVelocity() const
{
    Eigen::VectorXd fp_ = k->state();
    Vector3D res(fp_[3], fp_[4], fp_[5]);
//    res.print(cout);
    return res;
}
