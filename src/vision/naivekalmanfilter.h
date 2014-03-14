#ifndef NAIVEKALMANFILTER_H
#define NAIVEKALMANFILTER_H

//#include <eigen3/Eigen/Core>
//#include <eigen3/Eigen/LU>
//#include <eigen3/Eigen/Eigen>

#include "tools/vector3d.h"

struct FilterState {
    Vector3D acc;
    Vector3D vel;
    Vector3D pos;
};

class NaiveKalmanFilter
{
public:
    NaiveKalmanFilter();
    FilterState predict(double delta_t_sec);
    void observe(Vector3D new_pos, double delta_t_sec);
    FilterState filter();

    FilterState m_state;
private:
    FilterState m_observed;
    FilterState m_predicted;

//    FilterState m_pos_k_1;

    double alfa, beta, gama;

};

#endif // NAIVEKALMANFILTER_H
