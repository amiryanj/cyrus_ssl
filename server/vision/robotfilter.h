#ifndef _ROBOTFILTER_H
#define _ROBOTFILTER_H

#include <vector>
#include "sslframe.h"
#include "paramater-manager/parametermanager.h"

#define MAX_RAW_DATA_MEMORY 30
#define ROBOT_SPEED_LIMIT_FILTER 7

class RobotFilter
{
public:
    RobotFilter();

    void putNewFrame(OneObjectFrame &fr);
    bool isEmpty() const;
    bool isOnField() const;

    // main method for updating state vectors
    virtual bool run() = 0;
    Vector3D m_filteredPosition;
    Vector3D m_filteredVelocity;

    Vector3D m_rawPosition;
    Vector3D m_rawVelocity;

    bool hasUnprocessedData;

protected:
    std::vector<OneObjectFrame> rawData;
    OneObjectFrame& getRawData(uint i) {return rawData[i];}
    double last_update_time_msec;
    double last_dt_msec;
    double last_run_time_msec;

};

#endif // _ROBOTFILTER_H
