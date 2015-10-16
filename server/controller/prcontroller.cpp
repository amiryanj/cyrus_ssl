#include "prcontroller.h"
#include <QElapsedTimer>
#include <iostream>
PRController::PRController()
{
    timer = new QElapsedTimer;
    timer->start();
    Ratio = 0.1;
}

double PRController::CalculateVelocity(Vector3D target, Vector3D myPos,double currentSpeed)
{
    double timeElapsed = (double)timer->restart() / 1000;

    timeElapsed*=10;
 //   std::cout<currentSpeed<<std::endl;
    double RemainingDistance = (target - myPos).lenght2D();
    if(currentSpeed * timeElapsed > RemainingDistance)
        Ratio *= 0.1;
    else
        Ratio /= 0.1;
    if(Ratio > 1.0)
        Ratio = 1.0;
    return MaxSpeed * Ratio;
}

