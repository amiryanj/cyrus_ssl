#include "VisionFilter.h"

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
            robotFilter[i][j] = new RobotFilter();

    ballFilter = new BallFilter();
}

void VisionFilter::check()
{
    for(int tm=0; tm<NUM_TEAMS; ++tm)
        for(int i=0; i<MAX_ID_NUM; ++i)
        {
            robotFilter[tm][i]->runFilter();
        }

    ballFilter->runFilter();

    updateWorldModel();

}


void VisionFilter::setRobotFrame(SSL::Color color, unsigned int id, Frame &fr)
{
//    if(fr.camera_id == 1 && fabs(fr.position.X()) < 100)
//        return;
    if(((int) color > 2) || (id >= MAX_ID_NUM))
        throw "invalid color or id of robot";
    robotFilter[color][id]->putNewFrame(fr);
}

void VisionFilter::setBallFrame(Frame &fr)
{
    if(fr.camera_id == 1 && fabs(fr.position.X()) < 300)
        return;

    if(fabs(fr.position.X() > (30 + FIELD_LENGTH / 2))  ||  fabs(fr.position.Y())> (30 +FIELD_WIDTH / 2))
        return;

    ballFilter->putNewFrame(fr);
}

void VisionFilter::updateWorldModel()
{
    for(int i=0; i<NUM_TEAMS; ++i)
        for(int j=0; j<MAX_ID_NUM; ++j)
        {
            world->updateRobotState((SSL::Color)i, j,robotFilter[i][j]->getFilteredPosition(),
                                                  robotFilter[i][j]->getFilteredSpeed());
            world->updateRobotAvailability((SSL::Color)i, j, robotFilter[i][j]->isOnField());
        }

    world->updateBallState(0, ballFilter->getFilteredPosition(),
                           ballFilter->getUnfilteredSpeed(), ballFilter->getMedianFilteredSpeed());

}
