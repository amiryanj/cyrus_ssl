#include "KalmanModule.h"

KalmanModule::KalmanModule()
{
    for(int i=0; i<NUM_TEAMS; ++i)
        for(int j=0; j<MAX_ID_NUM; ++j)
            robotFilter[i][j] = new SSLRobotKalmanFilter();
}

void KalmanModule::check()
{
    for(int i=0; i<NUM_TEAMS; ++i)
        for(int j=0; j<MAX_ID_NUM; ++j)
            robotFilter[i][j]->runFilter();

}
