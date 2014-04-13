#include "pidcontroller.h"
#include <cmath>
#include <iostream>

PIDController::PIDController()
{
    m_crop_control.set(.92, .97, .15 * M_PI);
    this->setParameters(0.03, 0.02, 0.0);
//    this->setParameters(0.0, 0.0, 0.0);
}

void PIDController::setParameters(double kp, double ki, double kd)
{
    this->k_p = kp;
    this->k_i = ki;
    this->k_d = kd;
}

void PIDController::setPoint(Vector3D desired, Vector3D actual)
{
    currentDesired = desired;
    currentActual = actual;
    last_error = currentDesired - currentActual;

    if(fabs(desired.lenght2D()) < fabs(actual.lenght2D())) { // brake the robot
        last_error.setX(last_error.X() * 1.3);
        last_error.setY(last_error.Y() * 1.3);

        /*Vector3D temp =  last_error * k_p * 2;*/
    }
    else {
//        Vector3D temp =  last_error * k_p ;
    }

    sum_on_time *= 0.93;
    sum_on_time += last_error;

//    errorHistory.insert(errorHistory.begin(), last_error);
//    if(errorHistory.size() > MAX_HISTORY_SIZE)
//        errorHistory.pop_back();
}

void PIDController::clearHistory()
{
    this->errorHistory.clear();
}

Vector3D PIDController::getControl()
{
    Vector3D control;
    try {
        if(k_p < 0 || k_i < 0 || k_d<0)
            throw "Invalid Parameters";
//        if(errorHistory.size() < 1)
//            throw "There is no set point!";
        control += last_error * k_p;

//        Vector3D errorSum(0, 0, 0);
//        for(int i=0; i<errorHistory.size(); i++)
//            errorSum += errorHistory[i]/pow(1.1, i);
//        control += errorSum * k_i;

        control += sum_on_time * k_i;

        if(errorHistory.size() < 2)
            throw "There is no enough set point!";
        Vector3D d_error = errorHistory.at(0) - errorHistory.at(1);
        control += d_error * k_d;

        this->lastOutput = control;
    }
    catch (const char* msg)  {
        cerr << "Exception: " << "PID COntroller" << msg << endl;
    }

    control = control + currentDesired;

    if(control.X() > m_crop_control.X())
        control.setX(m_crop_control.X());
    else if(control.X() < - m_crop_control.X())
        control.setX(-m_crop_control.X());

    if(control.Y() > m_crop_control.Y())
        control.setY(m_crop_control.Y());
    else if(control.Y() < - m_crop_control.Y())
        control.setY(-m_crop_control.Y());

    if(control.Teta() > m_crop_control.Teta())
        control.setTeta(m_crop_control.Teta());
    else if(control.Teta() < - m_crop_control.Teta())
        control.setTeta(-m_crop_control.Teta());

    return control;

}
