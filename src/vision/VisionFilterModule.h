#ifndef VISIONFILTERMODULE_H
#define VISIONFILTERMODULE_H

#include "../general.h"
#include "../tools/SSLListener.h"
#include "SSLRobotKalmanFilter.h"
#include "frame.h"
#include "../ai/SSLWorldModel.h"
#include "naivekalmanfilter.h"

class VisionFilter : public SSLListener
{
    VisionFilter();
    static VisionFilter* module;

public:
    static VisionFilter* getInstance();
    void check();
    void setRobotFrame(Color color, unsigned int id, frame &fr);
    void setBallFrame(frame &fr);

private:
    SSLRobotKalmanFilter *robotFilter[NUM_TEAMS][MAX_ID_NUM];

    void updateWorldRobots();
    SSLWorldModel* world();

    NaiveKalmanFilter naiveFilter;

};

#endif // VISIONFILTERMODULE_H
