#ifndef _ALPHABETAFILTER_H
#define _ALPHABETAFILTER_H

#include "../../common/math/vector3d.h"
#include "../../common/sslnamespace.h"

using namespace SSL;

class AlphaBetaFilter
{
public:
    AlphaBetaFilter();

    void observe(Vector3D new_pos, Vector3D new_vel, Vector3D new_acc);
    SSLObjectState predict(double delta_t_sec);
    SSLObjectState filter();


    double m_alfa, m_beta, m_gama;
    double m_acc_effect;
    double m_speed_discount_rate;

    Vector3D max_speed_crop;
    Vector3D max_acceleration_crop;

private:
    SSLObjectState m_state;
    SSLObjectState m_observed;
    SSLObjectState m_predicted;
};

#endif // _ALPHABETAFILTER_H
