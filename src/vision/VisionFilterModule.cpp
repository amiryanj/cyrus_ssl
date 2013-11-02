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

SSLWorldModel *VisionFilterModule::world()
{
    return SSLWorldModel::getInstance();
}

void VisionFilterModule::check()
{
    for(int i=0; i<NUM_TEAMS; ++i)
        for(int j=0; j<MAX_ID_NUM; ++j)
        {
            robotFilter[i][j]->runFilter();            
        }

    updateWorldRobots();

}


void VisionFilterModule::setRobotFrame(Color color, unsigned int id, frame &fr)
{
    if(((int) color > 2) || (id >= MAX_ID_NUM))
        throw;
    robotFilter[color][id]->setNewFrame(fr);
}

void VisionFilterModule::setBallFrame(frame &fr)
{
    world()->updateBallState(0, fr.position.to2D(), Vector3D(0,0,0).to2D());
}

void VisionFilterModule::updateWorldRobots()
{
    for(int i=0; i<NUM_TEAMS; ++i)
        for(int j=0; j<MAX_ID_NUM; ++j)
        {
            world()->updateRobotState((Color)i, j,robotFilter[i][j]->getFilteredPosition(),
                                                    robotFilter[i][j]->getFilteredSpeed());
            world()->updateRobotAvailability((Color)i, j, robotFilter[i][j]->isOnField());
        }

}
