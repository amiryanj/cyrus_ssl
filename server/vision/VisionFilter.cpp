#include "VisionFilter.h"
#include "../definition/SSLBall.h"

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

//    if(fr.camera_id == 1)
//        return;
//    if(fr.camera_id == 1 && fabs(fr.position.X()) < 100)
//        return;
    if(((int) color > 2) || (id >= MAX_ID_NUM))
        throw "invalid color or id of robot";
    robotFilter[color][id]->putNewFrame(fr);
}

void VisionFilter::setBallFrames(vector<Frame> frs)
{
    for (int j = 0; j<MAX_BALL_NUM; j++) {
        if(frs.empty())
            break;
        float min_dist = INFINITY;
        short candid_id = 0;
        for(int i=0; i<frs.size(); i++) {
            float dist_i = (world->balls[j]->Position() - frs[i].position.to2D()).lenght();
            if(dist_i < min_dist) {
                candid_id = j;
                min_dist = dist_i;
            }
        }
        if(j==0)
            ballFilter->putNewFrame(frs[candid_id]);
        else
            world->balls[j]->setPosition(frs[candid_id].position.to2D());
        //    if(frs[candid_id].position.X() > 0)
        //      return;
        //    if(frs[candid_id].camera_id == 1)
        //      return;
        // skip out-of field balls, they are not important during a real game
        if(fabs(frs[candid_id].position.X() > (30 + FIELD_LENGTH / 2))
                ||  fabs(frs[candid_id].position.Y())> (30 +FIELD_WIDTH / 2))
            return;

        frs.erase(frs.begin() + candid_id);
    }
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
