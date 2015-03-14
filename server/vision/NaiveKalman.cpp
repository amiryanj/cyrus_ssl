#include "NaiveKalman.h"
#include "../../common/math/sslmath.h"
#include "../paramater-manager/parametermanager.h"
#include <cmath>

using namespace SSL;

NaiveKalman::NaiveKalman()
{
    // default parameters
    ParameterManager* pm = ParameterManager::getInstance();

    m_alfa = pm->get<double>("kalman.default.alfa");   // position coefficient
    m_beta = pm->get<double>("kalman.default.beta");   // velocity coefficient
    m_gama = pm->get<double>("kalman.default.gama");   // accelera coefficient

    m_acc_effect = pm->get<double>("kalman.default.acc_effect"); // default = 0
    m_speed_discount_rate = 0.9;

    max_speed_crop.set(10000, 10000, 3*M_PI);
    max_acceleration_crop.set(3000, 3000, 2*M_PI);
}

FilterState NaiveKalman::predict(double delta_t_sec)
{
    m_predicted.acc = m_state.acc;
    m_predicted.vel = m_state.vel * m_speed_discount_rate + (m_state.acc * delta_t_sec) * m_acc_effect;
    m_predicted.pos = m_state.pos + m_state.vel * delta_t_sec;// + m_state.acc * (0.5 * delta_t_sec *delta_t_sec);

    double teta_ = m_predicted.pos.Teta();
    m_predicted.pos.setTeta(continuousRadian(teta_, -M_PI));

    return m_predicted;
}

void NaiveKalman::observe(Vector3D new_pos, Vector3D new_vel, Vector3D new_acc)
{
    double teta_ = new_pos.Teta();
    if(m_observed.pos.Teta() > 0)
        new_pos.setTeta(continuousRadian(teta_, -M_PI_2));
    else
        new_pos.setTeta(continuousRadian(teta_, -3 * M_PI_2));

    m_observed.acc = new_acc;
    if(abs(m_observed.acc.X()) > max_acceleration_crop.X())
        m_observed.acc.setX(sgn(m_observed.acc.X())*max_acceleration_crop.X());

    if(abs(m_observed.acc.Y()) > max_acceleration_crop.Y())
        m_observed.acc.setY(sgn(m_observed.acc.Y())*max_acceleration_crop.Y());

    if(abs(m_observed.acc.Teta()) > max_acceleration_crop.Teta())
        m_observed.acc.setTeta(sgn(m_observed.acc.Teta())*max_acceleration_crop.Teta());

    m_observed.vel = new_vel;
    if(abs(m_observed.vel.X()) > max_speed_crop.X())
        m_observed.vel.setX(sgn(m_observed.vel.X())*max_speed_crop.X());

    if(abs(m_observed.vel.Y()) > max_speed_crop.Y())
        m_observed.vel.setY(sgn(m_observed.vel.Y())*max_speed_crop.Y());

    if(abs(m_observed.vel.Teta()) > max_speed_crop.Teta()) // radian/sec
        m_observed.vel.setTeta(sgn(m_observed.vel.Teta())*max_speed_crop.Teta());

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

    // crop the results
    if(abs(m_state.acc.X()) > max_acceleration_crop.X())
        m_state.acc.setX(sgn(m_state.acc.X())*max_acceleration_crop.X());

    if(abs(m_state.acc.Y()) > max_acceleration_crop.Y())
        m_state.acc.setY(sgn(m_state.acc.Y())*max_acceleration_crop.Y());

    if(abs(m_state.acc.Teta()) > max_acceleration_crop.Teta())
        m_state.acc.setTeta(sgn(m_state.acc.Teta())*max_acceleration_crop.Teta());

    if(abs(m_state.vel.X()) > max_speed_crop.X())
        m_state.vel.setX(sgn(m_state.vel.X())*max_speed_crop.X());

    if(abs(m_state.vel.Y()) > max_speed_crop.Y())
        m_state.vel.setY(sgn(m_state.vel.Y())*max_speed_crop.Y());

    if(abs(m_state.vel.Teta()) > max_speed_crop.Teta()) // radian/sec
        m_state.vel.setTeta(sgn(m_state.vel.Teta())*max_speed_crop.Teta());
    //

    teta_ = m_state.pos.Teta();
    m_state.pos.setTeta(continuousRadian(teta_, -M_PI));

    if(m_state.vel.lenght2D() > 4000) {
        std::cout << "HEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEY" << std::endl;
    }

    return m_state;
}
