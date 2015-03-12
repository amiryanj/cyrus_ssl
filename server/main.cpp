#include "ai/SSLGame.h"
#include "vision/SSLVision.h"
#include "vision/VisionFilter.h"
#include "referee/SSLReferee.h"
#include "general.h"
//#include <QVector3D>

#include "ai/SSLAnalyzer.h"
#include "gui/guihandler.h"
#include "transmitter/commandtransmitter.h"
#include "paramater-manager/parametermanager.h"
//#include "tools/sslmath.h"
using namespace std;

//******************************************************
#define OUR_COLOR   SSL::Blue
#define OUR_SIDE    SSL::Right
//******************************************************

int main(int argc, char *argv[])
{
    ParameterManager* pm = ParameterManager::getInstance();


    cout << "Parameter Manager initiated" <<endl;
    cout << "Main is running ... " << endl;
    long loopCounter = 0;

    SSLReferee *referee = new SSLReferee(pm->get<int>("network.REFEREE_PORT"),
                                         pm->get<string>("network.REFEREE_ADDRESS"));

    SSLVision *vision = new SSLVision(pm->get<int>("network.VISION_PORT"),
                                      pm->get<string>("network.VISION_ADDRESS"));

    VisionFilter *filter =  VisionFilter::getInstance();

    SSLGame *gameModule = SSLGame::getInstance((Color)pm->get<int>("game.our_color"),
                                               (Side)pm->get<int>("game.our_side"));

    GUIHandler *gui = GUIHandler::getInstance();

    CommandTransmitter* transmitter = CommandTransmitter::getInstance();

    transmitter->type = CommandTransmitter::GRSIM;

    while (true)
    {
        loopCounter ++;
        referee->check();
//        vision->check(); // in thread 2
//        filter->check(); // in thread 2
        analyzer->check();
        if((loopCounter % 10) ==0) {
            gameModule->check();
            transmitter->check();
        }
        if(loopCounter % 25 == 0)  {
            gui->check();
//            gui->testVisualizer();
        }
        usleep(2000);
    }
}
