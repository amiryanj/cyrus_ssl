#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H

#include <vector>
#include "../../shared/utility/vector3d.h"
#include "../../shared/utility/vector2d.h"

#define MAX_HISTORY_SIZE  20
using namespace std;

class PIDController
{
public:
    PIDController();
    void setParameters(double kp, double ki, double kd);
    void setPoint(const Vector3D &desired, const Vector3D &actual);
    void clearHistory();
    Vector3D getControl();


    Vector3D lastApplied;
private:
    double k_p, k_i, k_d;
    vector<Vector3D> errorHistory;

    Vector3D m_crop_control;
    Vector3D last_error;

//    Vector3D currentActual;
    Vector3D lastDesired;
    Vector3D sum_on_time;

    double lastAppliedTime_ms;

};

#endif // PIDCONTROLLER_H
