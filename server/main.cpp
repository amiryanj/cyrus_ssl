#include "ai/SSLGame.h"
#include "ai/SSLAnalyzer.h"

#include <time.h>

#include "vision/SSLVision.h"
#include "vision/VisionFilter.h"
#include "referee/SSLReferee.h"
#include "gui/guihandler.h"
#include "transmitter/commandtransmitter.h"
#include "paramater-manager/parametermanager.h"
#include "test/testvisioninput.h"
#include "test/testskills.h"
#include "test/testreferee.h"
#include "test/testmathfunctions.h"
#include "log-tools/logger.h"
#include "log-tools/networkplotter.h"

#include "general.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout << "Main is running ... " << endl;

    srand(time(0));
//    SSL::server_startup_time = currentTimeMSec();

    ParameterManager* pm = ParameterManager::getInstance();

    SSLReferee *referee = new SSLReferee(pm->get<int   >("network.REFEREE_PORT"),
                                         pm->get<string>("network.REFEREE_ADDRESS"));

    SSLVision *vision = new SSLVision(pm->get<int   >("network.VISION_PORT"),
                                      pm->get<string>("network.VISION_ADDRESS"));

    VisionFilter *filter =  VisionFilter::getInstance();

    SSLGame *gameModule = SSLGame::getInstance((Color)pm->get<int>("general.game.our_color"),
                                               (Side )pm->get<int>("general.game.our_side"));

    GUIHandler *gui = GUIHandler::getInstance();

    CommandTransmitter* transmitter = CommandTransmitter::getInstance();
    transmitter->type = CommandTransmitter::SERIAL;

    TestVisionInput* vision_tester = new TestVisionInput();
    TestSkills* gotopoint_tester = new TestSkills();
    TestReferee* referee_tester = new TestReferee();

//    Test::testVelocityStrenght();

    long loopCounter = 0;
    while ( true )
    {
        loopCounter ++;
        referee->check();
        referee_tester->check();

//        vision->check(); // in thread 2
        analyzer->check();
        if((loopCounter % 10) ==0) {
            double tic = SSL::currentTimeMSec();
            gameModule->check();
            double toc = SSL::currentTimeMSec();
            double process_time = toc - tic;
//            NetworkPlotter::getInstance()->buildAndSendPacket("Process Time", process_time);
            printf("Process Time = \t%f milli second\n", process_time);

//            transmitter->clear();
            gotopoint_tester->testKickBall();

            transmitter->check();
        }
        if(loopCounter % 40 == 0)   {
            vision_tester->check();
            filter->check();
            gui->check();
        }
        usleep(1000);
    }
}
