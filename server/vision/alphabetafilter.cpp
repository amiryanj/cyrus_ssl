#include "alphabetafilter.h"
#include "../../shared/utility/generalmath.h"
#include "../paramater-manager/parametermanager.h"
#include <cmath>

AlphaBetaFilter::AlphaBetaFilter()
{
    // default parameters
    ParameterManager* pm = ParameterManager::getInstance();

    m_alfa = pm->get<double>("vision.filter.default.alfa");   // position coefficient
    m_beta = pm->get<double>("vision.filter.default.beta");   // velocity coefficient
    m_gama = pm->get<double>("vision.filter.default.gama");   // accelera coefficient

    m_acc_effect = pm->get<double>("vision.filter.default.acc_effect"); // default = 0
    m_speed_discount_rate = 0.9;

    max_speed_crop.set(10000, 10000, 3*M_PI);
    max_acceleration_crop.set(3000, 3000, 2*M_PI);
}

void AlphaBetaFilter::observe(Vector3D new_pos, Vector3D new_vel, Vector3D new_acc)
{
    if(m_observed.pos.Teta() > 0)
        new_pos.setTeta(continuousRadian(new_pos.Teta(), -M_PI_2));
    else
        new_pos.setTeta(continuousRadian(new_pos.Teta(), -3 * M_PI_2));

    /// crop the results
    m_observed.acc.set( bound(new_acc.X(),
                                  -max_acceleration_crop.X(),
                                   max_acceleration_crop.X()) ,
                        bound(new_acc.Y(),
                                  -max_acceleration_crop.Y(),
                                   max_acceleration_crop.Y()) ,
                        bound(new_acc.Teta(),
                                  -max_acceleration_crop.Teta(),
                                   max_acceleration_crop.Teta()) );

    m_observed.vel.set( bound(new_vel.X(),
                                  -max_speed_crop.X(),
                                   max_speed_crop.X()) ,
                        bound(new_vel.Y(),
                                  -max_speed_crop.Y(),
                                   max_speed_crop.Y()) ,
                        bound(new_vel.Teta(),
                                  -max_speed_crop.Teta(),
                                   max_speed_crop.Teta()) );

    m_observed.pos = new_pos;
}

SSLObjectState AlphaBetaFilter::predict(double delta_t_sec)
{
    m_predicted.acc = m_state.acc;
    m_predicted.vel = m_state.vel * m_speed_discount_rate + (m_state.acc * delta_t_sec) * m_acc_effect;
    m_predicted.pos = m_state.pos + m_state.vel * delta_t_sec;// + m_state.acc * (0.5 * delta_t_sec *delta_t_sec);

    m_predicted.pos.setTeta(continuousRadian(m_predicted.pos.Teta(), -M_PI));

    return m_predicted;
}

SSLObjectState AlphaBetaFilter::filter()
{
    double teta_ = m_predicted.pos.Teta();
    if(m_observed.pos.Teta() > 0)
        m_predicted.pos.setTeta(continuousRadian(teta_, -M_PI_2));
    else
        m_predicted.pos.setTeta(continuousRadian(teta_, -3 * M_PI_2));

    m_state.pos = m_predicted.pos * (1-m_alfa) + m_observed.pos * m_alfa;
    m_state.vel = m_predicted.vel * (1-m_beta) + m_observed.vel * m_beta;

    m_state.acc = m_predicted.acc * (1-m_gama) + m_observed.acc * m_gama;

    /// crop the results
    m_state.acc.set( bound(m_state.acc.X(),
                                -max_acceleration_crop.X(),
                                 max_acceleration_crop.X()) ,
                     bound(m_state.acc.Y(),
                                -max_acceleration_crop.Y(),
                                 max_acceleration_crop.Y()) ,
                     bound(m_state.acc.Teta(),
                                -max_acceleration_crop.Teta(),
                                 max_acceleration_crop.Teta()) );

    m_state.vel.set( bound(m_state.vel.X(),
                                -max_speed_crop.X(),
                                 max_speed_crop.X()) ,
                     bound(m_state.vel.Y(),
                                -max_speed_crop.Y(),
                                 max_speed_crop.Y()) ,
                     bound(m_state.vel.Teta(),
                                -max_speed_crop.Teta(),
                                 max_speed_crop.Teta()) );


    teta_ = m_state.pos.Teta();
    m_state.pos.setTeta(continuousRadian(teta_, -M_PI));

    return m_state;
}
