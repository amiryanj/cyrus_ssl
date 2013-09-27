#ifndef VISIONFILTERMODULE_H
#define VISIONFILTERMODULE_H

#include "general.h"
#include "tools/SSLListener.h"
#include "SSLRobotKalmanFilter.h"
#include "frame.h"

class VisionFilterModule : public SSLListener
{
public:
    static VisionFilterModule* getInstance();
    void check();
    void setRobotFrame(Color color, unsigned int id, const frame &fr);

protected:    
    VisionFilterModule();
    SSLRobotKalmanFilter *robotFilter[NUM_TEAMS][MAX_ID_NUM];

    static VisionFilterModule* module;


};

#endif // VISIONFILTERMODULE_H
