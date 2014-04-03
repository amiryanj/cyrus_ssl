#include "NaiveKalman.h"
#include "tools/sslmath.h"
#include <cmath>

using namespace SSL;

NaiveKalman::NaiveKalman()
{
    // default parameters
    m_alfa = 0.25;
    m_beta = 0.05;
    m_gama = 0.15;

    m_acc_effect = 0.0;

    max_speed_crop.set(3000, 3000, 3*M_PI);
    max_acceleration_crop.set(3000, 3000, 2*M_PI);
}

FilterState NaiveKalman::predict(double delta_t_sec)
{
    m_predicted.acc = m_state.acc;
    m_predicted.vel = m_state.vel + (m_state.acc * delta_t_sec) * m_acc_effect;
    m_predicted.pos = m_state.pos + m_state.vel * delta_t_sec;// + m_state.acc * (0.5 * delta_t_sec *delta_t_sec);

    double teta_ = m_predicted.pos.Teta();
    m_predicted.pos.setTeta(continuousRadian(teta_, -M_PI));

    return m_predicted;
}

void NaiveKalman::observe(Vector3D new_pos, double delta_t_sec)
{
    double teta_ = new_pos.Teta();
    if(m_observed.pos.Teta() > 0)
        new_pos.setTeta(continuousRadian(teta_, -M_PI_2));
    else
        new_pos.setTeta(continuousRadian(teta_, -3 * M_PI_2));

    m_observed.acc = (((new_pos - m_observed.pos) / delta_t_sec) - m_observed.vel)/delta_t_sec ;
    if(m_observed.acc.X() > max_acceleration_crop.X())
        m_observed.acc.setX(max_acceleration_crop.X());
    if(m_observed.acc.Y() > max_acceleration_crop.Y())
        m_observed.acc.setY(max_acceleration_crop.Y());
    if(m_observed.acc.Teta() > max_acceleration_crop.Teta())
        m_observed.acc.setTeta(max_acceleration_crop.Teta());

    m_observed.vel = (new_pos - m_observed.pos) / delta_t_sec;
    if(m_observed.vel.X() > max_speed_crop.X())
        m_observed.vel.setX(max_speed_crop.X());
    else if(m_observed.vel.X() < -max_speed_crop.X())
        m_observed.vel.setX(-max_speed_crop.X());

    if(m_observed.vel.Y() > max_speed_crop.Y())
        m_observed.vel.setY(max_speed_crop.Y());
    if(m_observed.vel.Y() < -max_speed_crop.Y())
        m_observed.vel.setY(-max_speed_crop.Y());

    if(m_observed.vel.Teta() > max_speed_crop.Teta()) // radian/sec
        m_observed.vel.setTeta(max_speed_crop.Teta());
    if(m_observed.vel.Teta() < -max_speed_crop.Teta()) // radian/sec
        m_observed.vel.setTeta(-max_speed_crop.Teta());

    m_observed.pos = new_pos;
}

FilterState NaiveKalman::filter()
{
    double teta_ = m_predicted.pos.Teta();
    if(m_observed.pos.Teta() > 0)
        m_predicted.pos.setTeta(continuousRadian(teta_, -M_PI_2));
    else
        m_predicted.pos.setTeta(continuousRadian(teta_, -3 * M_PI_2));

    m_state.pos = m_predicted.pos * (1-m_alfa) + m_observed.pos * m_alfa;
    m_state.vel = m_predicted.vel * (1-m_beta) + m_observed.vel * m_beta;

    m_state.acc = m_predicted.acc * (1-m_gama) + m_observed.acc * m_gama;
    if(m_state.acc.lenght2D() > 2000)
        m_state.acc /= 2;

    teta_ = m_state.pos.Teta();
    m_state.pos.setTeta(continuousRadian(teta_, -M_PI));

    if(m_state.vel.lenght2D() > 4000) {
        std::cout << "HEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEY" << std::endl;
    }

    return m_state;
}
