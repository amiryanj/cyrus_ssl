#include "naivekalmanfilter.h"
#include "tools/sslmath.h"
#include <cmath>

using namespace SSL;

NaiveKalmanFilter::NaiveKalmanFilter()
{
    alfa = 0.75;
    beta = 0.8;
    gama = 0.25;
}

FilterState NaiveKalmanFilter::predict(double delta_t_sec)
{
    m_predicted.acc = m_state.acc;
    m_predicted.vel = m_state.vel + m_state.acc * delta_t_sec;
    m_predicted.pos = m_state.pos + m_state.vel * delta_t_sec;// + m_state.acc * (0.5 * delta_t_sec *delta_t_sec);

    double teta_ = m_predicted.pos.Teta();
    m_predicted.pos.setTeta(continuousRadian(teta_, -M_PI));

    return m_predicted;
}

void NaiveKalmanFilter::observe(Vector3D new_pos, double delta_t_sec)
{
    double teta_ = new_pos.Teta();
    if(m_observed.pos.Teta() > 0)
        new_pos.setTeta(continuousRadian(teta_, -M_PI_2));
    else
        new_pos.setTeta(continuousRadian(teta_, -3 * M_PI_2));

    m_observed.acc = (((new_pos - m_observed.pos) / delta_t_sec) - m_observed.vel)/delta_t_sec ;
    if(m_observed.acc.lenght2D() > 5000)
        m_observed.acc.setZero();

    m_observed.vel = (new_pos - m_observed.pos) / delta_t_sec;
    if(m_observed.vel.lenght2D() > 5000)
        m_observed.vel.setZero();

    m_observed.pos = new_pos;
}

FilterState NaiveKalmanFilter::filter()
{
    double teta_ = m_predicted.pos.Teta();
    if(m_observed.pos.Teta() > 0)
        m_predicted.pos.setTeta(continuousRadian(teta_, -M_PI_2));
    else
        m_predicted.pos.setTeta(continuousRadian(teta_, -3 * M_PI_2));

    m_state.pos = m_predicted.pos * (1-alfa) + m_observed.pos * alfa;
    m_state.vel = m_predicted.vel * (1-beta) + m_observed.vel * beta;

    m_state.acc = m_predicted.acc * (1-gama) + m_observed.acc * gama;
    if(m_state.acc.lenght2D() > 5000)
        m_state.acc /= 2;

    teta_ = m_state.pos.Teta();
    m_state.pos.setTeta(continuousRadian(teta_, -M_PI));

    return m_state;
}
