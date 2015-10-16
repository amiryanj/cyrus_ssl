#ifndef PRCONTROLLER_H
#define PRCONTROLLER_H
#include<vector3d.h>
#include<QElapsedTimer>

class PRController
{
public:
    PRController();
    QElapsedTimer * timer;
    double Ratio = 0.0;
    const double MaxSpeed = 1000;
    double CalculateVelocity(Vector3D target,Vector3D myPos,double currentSpeed);


};

#endif // PRCONTROLLER_H
