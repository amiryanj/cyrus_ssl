#ifndef _ROBOTFILTER_H
#define _ROBOTFILTER_H

#include <vector>
#include <stdlib.h>
#include "sslframe.h"
#include "alphabetafilter.h"
#include "../../common/math/vector3d.h"
#include "../definition/SSLRobot.h"


#define MAX_RAW_DATA_MEMORY 30
#define MAX_ROBOT_MEDIAN_MEMORY 11
#define ROBOT_SPEED_LIMIT_FILTER 7

class RobotFilter //: public Kalman::EKFilter<double, 1>
{
    friend class VisionFilter;
    friend class MainWindow;
public:
    RobotFilter();
    void putNewFrame(const SSLFrame &fr);
    bool isEmpty();
    bool isOnField();

    // main method for updating state vectors
    void run();

private:
    std::vector<SSLRobotState> rawData;
    SSLRobotState& getRawData(uint i) {return rawData[i];}
    Vector3D rawSpeedList[MAX_ROBOT_MEDIAN_MEMORY];
    double last_update_time_msec;
    double last_delta_t_sec;

    Vector3D m_filteredPosition;
    Vector3D m_filteredSpeed;
    Vector3D m_medianFilteredSpeed;

    AlphaBetaFilter alphaBetaFilter;

    int __medianFilterIndex;

    bool hasUnprocessedData;
};

#endif // _ROBOTFILTER_H
