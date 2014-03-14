#include "VisionFilterModule.h"

VisionFilter* VisionFilter::module = NULL;

VisionFilter *VisionFilter::getInstance()
{
    if(module == NULL)
        module = new VisionFilter();
    return module;

}

VisionFilter::VisionFilter()
{
    for(int i=0; i<NUM_TEAMS; ++i)
        for(int j=0; j<MAX_ID_NUM; ++j)
            robotFilter[i][j] = new SSLRobotKalmanFilter();
}

SSLWorldModel *VisionFilter::world()
{
    return SSLWorldModel::getInstance();
}

void VisionFilter::check()
{
    for(int tm=0; tm<NUM_TEAMS; ++tm)
        for(int i=0; i<MAX_ID_NUM; ++i)
        {
            robotFilter[tm][i]->runFilter();
        }

    updateWorldRobots();


}


void VisionFilter::setRobotFrame(Color color, unsigned int id, frame &fr)
{
    if(((int) color > 2) || (id >= MAX_ID_NUM))
        throw "invalid color or id of robot";
    robotFilter[color][id]->putNewFrame(fr);
}

void VisionFilter::setBallFrame(frame &fr)
{
    world()->updateBallState(0, fr.position.to2D(), Vector3D(0,0,0).to2D());
}

void VisionFilter::updateWorldRobots()
{
    for(int i=0; i<NUM_TEAMS; ++i)
        for(int j=0; j<MAX_ID_NUM; ++j)
        {
            world()->updateRobotState((Color)i, j,robotFilter[i][j]->getFilteredPosition(),
                                                    robotFilter[i][j]->getFilteredSpeed());
            world()->updateRobotAvailability((Color)i, j, robotFilter[i][j]->isOnField());
        }

}
