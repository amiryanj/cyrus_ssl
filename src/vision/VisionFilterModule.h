#ifndef VISIONFILTERMODULE_H
#define VISIONFILTERMODULE_H

#include "../general.h"
#include "tools/SSLListener.h"
#include "SSLRobotKalmanFilter.h"
#include "frame.h"
#include "ai/SSLWorldModel.h"

class VisionFilterModule : public SSLListener
{
public:
    static VisionFilterModule* getInstance();
    void check();
    void setRobotFrame(Color color, unsigned int id, frame &fr);
    void setBallFrame(frame &fr);

private:
    VisionFilterModule();
    SSLRobotKalmanFilter *robotFilter[NUM_TEAMS][MAX_ID_NUM];

    static VisionFilterModule* module;

    SSLWorldModel* world;
    void updateWorldModel();

};

#endif // VISIONFILTERMODULE_H
