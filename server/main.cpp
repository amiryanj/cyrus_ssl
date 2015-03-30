#include "ai/SSLGame.h"
#include "ai/SSLAnalyzer.h"

#include "vision/SSLVision.h"
#include "vision/VisionFilter.h"
#include "referee/SSLReferee.h"
#include "gui/guihandler.h"
#include "transmitter/commandtransmitter.h"
#include "paramater-manager/parametermanager.h"
#include "test/testserver.h"

#include "general.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout << "Main is running ... " << endl;

    ParameterManager* pm = ParameterManager::getInstance();

    SSLReferee *referee = new SSLReferee(pm->get<int>("network.REFEREE_PORT"),
                                         pm->get<string>("network.REFEREE_ADDRESS"));

    SSLVision *vision = new SSLVision(pm->get<int>("network.VISION_PORT"),
                                      pm->get<string>("network.VISION_ADDRESS"));

    VisionFilter *filter =  VisionFilter::getInstance();

    SSLGame *gameModule = SSLGame::getInstance((Color)pm->get<int>("general.game.our_color"),
                                               (Side)pm->get<int>("general.game.our_side"));

    GUIHandler *gui = GUIHandler::getInstance();

    CommandTransmitter* transmitter = CommandTransmitter::getInstance();
    transmitter->type = CommandTransmitter::GRSIM;

    TestServer* tester = new TestServer();

    long loopCounter = 0;
    while (true)
    {
        loopCounter ++;
        referee->check();
//        vision->check(); // in thread 2
        analyzer->check();
        if((loopCounter % 10) ==0) {
            double tic = SSL::currentTimeMSec();
            gameModule->check();
            double toc = SSL::currentTimeMSec();
            double process_time = toc - tic;
            printf("Process Time = \t%f milli second\n", process_time);
            transmitter->check();
        }
        if(loopCounter % 15 == 0)  {
//            tester->check();
            filter->check();
            gui->check();
//            gui->testVisualizer();
        }
        usleep(1000);
    }
}
