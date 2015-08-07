#include "robotkalmanfilter.h"
#include "utility/generalmath.h"

RobotKalmanFilter::RobotKalmanFilter()
{
    KF.init();
    last_update_time_msec = currentTimeMSec();
    last_dt_msec = 1.0;
    hasUnprocessedData = false;
}

bool RobotKalmanFilter::run()
{
    try {
        if(!hasUnprocessedData) {
            throw "No new data to be processed";
        }
        if(rawData.empty())
        {
            throw "Filter is invoked without any data";
        }
        else if(rawData.size() == 1) {
            KF.init();
        }
        else {
            OneObjectFrame fr = rawData[0];
            KF.update(fr.position, fr.velocity, last_dt_msec/1000.0);
            m_filteredPosition = KF.getFilteredPosition();
            m_filteredVelocity = KF.getFilteredVelocity();
        }
        hasUnprocessedData = false;
        return true;

    } catch (const char* msg) {
//        cerr << "Error: Robot Kalman Filter: " << msg << endl;
        return false;
    }
}
