#ifndef _VISIONFILTER_H
#define _VISIONFILTER_H

#include "../../common/general.h"
#include "../ai/SSLWorldModel.h"
#include "../../common/tools/SSLListener.h"
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

    BallFilter *ballFilter;
private:
    RobotFilter *robotFilter[NUM_TEAMS][MAX_ID_NUM];


    void updateWorldModel();

};

#endif // _VISIONFILTER_H
