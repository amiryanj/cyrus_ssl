#include "pidcontroller.h"
#include <cmath>
#include <iostream>
#include <paramater-manager/parametermanager.h>
#include "../../common/math/sslmath.h"

PIDController::PIDController()
{
    m_crop_control.set(.92, .97, .15 * M_PI);

    //  this->setParameters(0.0, 0.0, 0.0);
    this->setParameters(0.1 /*Kp*/, 0.002 /*Ki*/, 0.0 /*Kd*/);
}

void PIDController::setParameters(double kp, double ki, double kd)
{    
    this->k_p = kp;
    this->k_i = ki;
    this->k_d = kd;
}

void PIDController::setPoint(Vector3D desired, Vector3D actual)
{
    const double max_speed = 3000;
    last_error = (desired - actual);
    last_error /= max_speed; // normalize the variable [-1, 1]
    lastDesired = desired;

    errorHistory.insert(errorHistory.begin(), last_error);
    if(errorHistory.size() > MAX_HISTORY_SIZE)
        errorHistory.pop_back();
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

        double delta_time = SSL::currentTimeMSec() - lastAppliedTime_ms;
        double diff_x = control.X() - lastApplied.X();
        if(fabs(control.X()) > fabs(lastApplied.X())) {
            double max_increse_limit_x = (delta_time/1000.0) * .6; // about .05 per
            if(fabs(diff_x) > max_increse_limit_x)
                control.setX(lastApplied.X() + max_increse_limit_x * SSL::sgn(diff_x));
        }  else  {
                // control.x doesnt change
        }

        if(fabs(control.Y()) > fabs(lastApplied.Y())) {
            double max_increse_limit_y = (delta_time/1000.0) * .6; // about .05 per
            double diff_y = control.Y() - lastApplied.Y();
            if(fabs(diff_y) > max_increse_limit_y)
                control.setY(lastApplied.Y() + max_increse_limit_y * SSL::sgn(diff_y));
        }  else  {
                // control.y doesnt change
        }

        if(control.lenght2D() > 1)
            control.normalize2D();
        lastApplied = control;

        control.setTeta(lastDesired.Teta());
        lastAppliedTime_ms = SSL::currentTimeMSec();
    }
    catch (const char* msg)  {
        cerr << "Exception: " << "PID COntroller: " << msg << endl;
    }

    return control;

}
