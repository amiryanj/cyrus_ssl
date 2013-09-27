#include "VisionFilterModule.h"

VisionFilterModule* VisionFilterModule::module = NULL;

VisionFilterModule *VisionFilterModule::getInstance()
{
    if(module == NULL)
        module = new VisionFilterModule();
    return module;

}

VisionFilterModule::VisionFilterModule()
{
    for(int i=0; i<NUM_TEAMS; ++i)
        for(int j=0; j<MAX_ID_NUM; ++j)
            robotFilter[i][j] = new SSLRobotKalmanFilter();
}

void VisionFilterModule::check()
{
    for(int i=0; i<NUM_TEAMS; ++i)
        for(int j=0; j<MAX_ID_NUM; ++j)
            robotFilter[i][j]->runFilter();

}


void VisionFilterModule::setRobotFrame(Color color, unsigned int id, const frame &fr)
{
    robotFilter[color][id]->setNewFrame(fr);
}
