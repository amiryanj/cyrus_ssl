#ifndef _VISIONFILTER_H
#define _VISIONFILTER_H

#include "../general.h"
#include "../ai/SSLWorldModel.h"
#include "SSLListener.h"
#include "RobotFilter.h"
#include "BallFilter.h"
#include "Frame.h"
#include "NaiveKalman.h"

class VisionFilter : public SSLListener
{
    VisionFilter();
    static VisionFilter* module;

public:
    static VisionFilter* getInstance();
    void check();
    void setRobotFrame(SSL::Color color, unsigned int id, Frame &fr);
    void setBallFrames(vector<Frame> frs);

private:
    RobotFilter *robotFilter[NUM_TEAMS][MAX_ID_NUM];

    BallFilter *ballFilter;

    void updateWorldModel();

};

#endif // _VISIONFILTER_H
