#include "ai/SSLGame.h"
#include "vision/SSLVision.h"
#include "general.h"
//#include <QVector3D>

#include "tools/stdlist.h"
#include "ai/SSLAnalyzer.h"
#include "gui/guihandler.h"
#include "transmitter/commandtransmitter.h"

#include "tools/sslmath.h"
using namespace std;



int main(int argc, char *argv[])
{
//    QApplication app(argc, argv);

//    double angle = -3*M_PI_4;
//    double start = 0;
//    cout << "for " << angle << " > "<< continuousRadian(angle, start) <<   endl;

    cout << "Main is running ... " << endl;
    long loopCounter = 0;

    SSLVision *vision = new SSLVision(GRSIM_VISION_PORT, GRSIM_VISION_ADDRESS);

    VisionFilter *filter =  VisionFilter::getInstance();

    SSLAnalyzer *analyzer = SSLAnalyzer::getInstance();

    SSLGame *game = SSLGame::getInstance(SSL::Blue, Right);

    GUIHandler *gui = GUIHandler::getInstance();

    CommandTransmitter* transmitter = CommandTransmitter::getInstance();

    transmitter->type = CommandTransmitter::SERIAL;

    while (true)
    {
        loopCounter ++;
        vision->check();
        filter->check();
        analyzer->check();
        if((loopCounter % 5) ==0) {
            game->check();
            gui->check();
        }
        if(loopCounter % 100 == 0)
            transmitter->check();
        usleep(5000);
    }

    //    return app.exec();
    // ------------ test scripts -------------------


}

