#include "robotfilter.h"
#include "utility/generalmath.h"

RobotFilter::RobotFilter()
{
    last_update_time_msec = 0;
    rawData.reserve(MAX_RAW_DATA_MEMORY + 1);
}

void RobotFilter::putNewFrame(OneObjectFrame &fr)
{
    try {
        hasUnprocessedData = true;
        last_update_time_msec = currentTimeMSec();

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

bool RobotFilter::isEmpty() const
{
    return rawData.empty();
}

bool RobotFilter::isOnField() const
{
    double dt = currentTimeMSec() - last_update_time_msec ;
    return (dt < 2000);
}
