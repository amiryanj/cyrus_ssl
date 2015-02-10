#include "ai/SSLGame.h"
#include "vision/SSLVision.h"
#include "vision/VisionFilter.h"
#include "referee/SSLReferee.h"
#include "general.h"
//#include <QVector3D>

#include "ai/SSLAnalyzer.h"
#include "gui/guihandler.h"
#include "transmitter/commandtransmitter.h"

//#include "tools/sslmath.h"
using namespace std;

//******************************************************
#define OUR_COLOR   SSL::Blue
#define OUR_SIDE    SSL::Left
//******************************************************

int main(int argc, char *argv[])
{
    cout << "Main is running ... " << endl;
    long loopCounter = 0;

    SSLReferee *referee = new SSLReferee(MY_REFEREE_PORT, MY_REFEREE_ADDRESS);

    SSLVision *vision = new SSLVision(GRSIM_VISION_PORT, GRSIM_VISION_ADDRESS);


    VisionFilter *filter =  VisionFilter::getInstance();

    SSLGame *gameModule = SSLGame::getInstance(OUR_COLOR, OUR_SIDE);

    GUIHandler *gui = GUIHandler::getInstance();

    CommandTransmitter* transmitter = CommandTransmitter::getInstance();

    transmitter->type = CommandTransmitter::SERIAL;

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
        }
        usleep(2000);
    }



}

