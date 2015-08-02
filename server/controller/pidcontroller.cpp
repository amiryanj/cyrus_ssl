#include "pidcontroller.h"
#include <cmath>
#include <iostream>
#include <paramater-manager/parametermanager.h>
#include "../../shared/utility/generalmath.h"
#include "../debug-tools/debugclient.h"

PIDController::PIDController()
{
    m_crop_control.set(.92, .97, .15 * M_PI);

    //  this->setParameters(0.0, 0.0, 0.0);
    this->setParameters(0.5 /*Kp*/, 0.002 /*Ki*/, 0.0 /*Kd*/);
    this->lastApplied.setZero();
}

void PIDController::setParameters(double kp, double ki, double kd)
{    
    this->k_p = kp;
    this->k_i = ki;
    this->k_d = kd;
}

void PIDController::setPoint(const Vector3D &desired, const Vector3D &actual)
{
    const double max_speed = 3000;
    last_error = (desired - actual);
    last_error /= max_speed; // normalize the variable [-1, 1]
    lastDesired = desired;

    errorHistory.insert(errorHistory.begin(), last_error);
    if(errorHistory.size() > MAX_HISTORY_SIZE)
        errorHistory.pop_back();

    Debugger::dbg()->print("PID Controller set point");
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

        const double max_speed = 3000;
        control = lastDesired/max_speed; // normalize the variable [-1, 1]
        control += last_error * k_p;

        double delta_time = std::min((currentTimeMSec() - lastAppliedTime_ms)/1000.0, 0.1);
        double max_increase_limit = 0.5 * delta_time; // about .05 per

        Vector3D control_diff = control - lastApplied;
        if(fabs(control.X()) > fabs(lastApplied.X())) {
            if(fabs(control_diff.X()) > max_increase_limit)
                control.setX(lastApplied.X() + max_increase_limit * sgn(control_diff.X()));
        }  else  {
                // control.x doesnt change
        }

        if(fabs(control.Y()) > fabs(lastApplied.Y())) {
            if(fabs(control_diff.Y()) > max_increase_limit)
                control.setY(lastApplied.Y() + max_increase_limit * sgn(control_diff.Y()));
        }  else  {
                // control.y doesnt change
        }

        double max_omega_increase_limit = 0.5 * delta_time; // about .05 per
        if(fabs(control.Teta()) > fabs(lastApplied.Teta()))
            if(fabs(control_diff.Teta()) > max_omega_increase_limit)
                control.setTeta(lastApplied.Teta() + max_omega_increase_limit * sgn(control_diff.Teta()));

        if(control.lenght2D() > 1)
            control.normalize2D();
        lastApplied = control;

        control.setTeta(lastDesired.Teta());
        lastAppliedTime_ms = currentTimeMSec();
    }
    catch (const char* msg)  {
        cerr << "Exception: " << "PID COntroller: " << msg << endl;
    }

    return control;

}
