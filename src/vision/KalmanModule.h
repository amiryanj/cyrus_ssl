#ifndef KALMANMODULE_H
#define KALMANMODULE_H

#include "general.h"
#include "tools/SSLListener.h"
#include "SSLRobotKalmanFilter.h"

class KalmanModule : public SSLListener
{
public:

    KalmanModule();
    void check();

protected:
    SSLRobotKalmanFilter *robotFilter[NUM_TEAMS][MAX_ID_NUM];


};

#endif // KALMANMODULE_H
