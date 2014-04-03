#ifndef _ROBOTFILTER_H
#define _ROBOTFILTER_H

#include "../tools/vector3d.h"
#include "NaiveKalman.h"
#include "Frame.h"

#define MAX_RAW_DATA_MEMORY 30

class RobotFilter //: public Kalman::EKFilter<double, 1>
{
public:
    RobotFilter();
    void putNewFrame(const Frame &fr);
    bool isEmpty();
    bool isOnField();

    // main method for updating state vectors
    void runFilter();

    Vector3D getFilteredSpeed() const;
    Vector3D getFilteredPosition() const;

private:
    std::vector<Frame> rawPositionList;
    double last_update_time_msec;
    double last_delta_t_sec;

    Vector3D m_filteredPosition;
    Vector3D m_filteredSpeed;

    NaiveKalman naiveFilter;

};

#endif // _ROBOTFILTER_H
