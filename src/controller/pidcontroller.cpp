#include "pidcontroller.h"
#include <cmath>
#include <iostream>

PIDController::PIDController()
{

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
    Vector3D error = currentActual - currentDesired;
    errorHistory.insert(errorHistory.begin(), error);
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
        if(errorHistory.size() < 1)
            throw "There is no set point!";
        control += errorHistory.at(0) * k_p;

        Vector3D errorSum(0, 0, 0);
        for(int i=0; i<errorHistory.size(); i++)
            errorSum += errorHistory.at(i)/pow(2, i);
        control += errorSum * k_i;

        if(errorHistory.size() < 2)
            throw "There is no enough set point!";
        Vector3D d_error = errorHistory.at(0) - errorHistory.at(1);
        control += d_error * k_d;

        this->lastOutput = control;
    }
    catch (const char* msg)  {
        cerr << "Exception: " << "PID COntroller" << msg << endl;
    }

    return control + currentDesired;
}
