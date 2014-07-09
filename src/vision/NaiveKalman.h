#ifndef _NAIVEKALMAN_H
#define _NAIVEKALMAN_H

//#include <eigen3/Eigen/Core>
//#include <eigen3/Eigen/LU>
//#include <eigen3/Eigen/Eigen>

#include "math/vector3d.h"

struct FilterState {
    Vector3D acc;
    Vector3D vel;
    Vector3D pos;
};

class NaiveKalman
{
public:
    NaiveKalman();
    FilterState predict(double delta_t_sec);
    void observe(Vector3D new_pos, double delta_t_sec);
    FilterState filter();

    FilterState m_state;

    double m_alfa, m_beta, m_gama;
    double m_acc_effect;

    Vector3D max_speed_crop;
    Vector3D max_acceleration_crop;
private:
    FilterState m_observed;
    FilterState m_predicted;

//    FilterState m_pos_k_1;


};

#endif // _NAIVEKALMAN_H
