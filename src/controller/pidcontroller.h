#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H

#include <vector>
#include "../tools/vector3d.h"

#define MAX_HISTORY_SIZE  20
using namespace std;

class PIDController
{
public:
    PIDController();
    void setParameters(double kp, double ki, double kd);
    void setPoint(Vector3D desired, Vector3D actual);
    void clearHistory();
    Vector3D getControl();
    void autoTune();
    Vector3D lastOutput;

private:
    double k_p, k_i, k_d;
    vector<Vector3D> errorHistory;
    Vector3D currentActual;
    Vector3D currentDesired;

};

#endif // PIDCONTROLLER_H
