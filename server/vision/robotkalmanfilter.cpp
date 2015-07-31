#include "robotkalmanfilter.h"
#include "utility/generalmath.h"

RobotKalmanFilter::RobotKalmanFilter()
{
    KF.init();
    last_time_msec = currentTimeMSec();
    last_dt_msec = 1.0;
    hasUnprocessedData = false;
}

void RobotKalmanFilter::putNewFrame(OneObjectFrame &fr)
{
    try {
        hasUnprocessedData = true;
        last_time_msec = currentTimeMSec();

        if( rawData.empty() ) {
            fr.velocity.setZero();
            fr.acceleration.setZero();            
        }
        else {
            OneObjectFrame previous_frame = rawData[0];
            double dt_msec = fr.timeStampMSec - previous_frame.timeStampMSec;
            last_dt_msec = dt_msec;
            if(dt_msec == 0)
                throw "problem division by zero, delta_t is 0!!!";

            continuousRadian(fr.position.Teta(), previous_frame.position.Teta()-M_PI);
            fr.velocity = (fr.position - previous_frame.position) * 1000.0/dt_msec;
            fr.acceleration = (fr.velocity - previous_frame.velocity) * 1000.0/dt_msec;

        }
        m_rawPosition = fr.position;
        m_rawVelocity = fr.velocity;

        rawData.insert(rawData.begin(), fr);
        if(rawData.size() > 10 /*MAX_RAW_DATA_MEMORY*/)
            rawData.pop_back();

//        run();

    } catch (const char* msg) {
        cerr << "Warning: Robot Kalman Filter: " << msg << endl;
    }
}

bool RobotKalmanFilter::isEmpty() const
{
    return rawData.empty();
}

bool RobotKalmanFilter::isOnField() const
{
//    cout << "currentTimeMSec: " << currentTimeMSec() << endl;
    double dt = currentTimeMSec() - last_time_msec ;
    bool res = dt < 2000;
    return res;
}

void RobotKalmanFilter::run()
{
    try {
        if(!hasUnprocessedData)
            throw "No new data to be processed";
        if(rawData.empty())
        {
//            throw "Filter is invoked without any data";
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

    } catch (const char* msg) {
        cerr << "Error: Robot Kalman Filter: " << msg << endl;
    }
}
