#ifndef __ROBOTFILTER_H
#define __ROBOTFILTER_H

#include <vector>
#include "sslframe.h"
#include "paramater-manager/parametermanager.h"

class RobotFilter
{
public:
    RobotFilter();

    void putNewFrame(OneObjectFrame &fr);
    bool isEmpty() const;
    bool isOnField() const;

    // main method for updating state vectors
    virtual void run() = 0;
    Vector3D m_filteredPosition;
    Vector3D m_filteredVelocity;

    Vector3D m_rawPosition;
    Vector3D m_rawVelocity;

    bool hasUnprocessedData;

protected:
    std::vector<OneObjectFrame> rawData;
    double last_time_msec;
    double last_dt_msec;

};

#endif // __ROBOTFILTER_H
