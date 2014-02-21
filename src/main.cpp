#include "ai/SSLGame.h"
#include "vision/SSLVision.h"
#include "general.h"
//#include <QVector3D>

#include "tools/stdlist.h"
#include "ai/SSLAnalyzer.h"
#include "gui/guihandler.h"
#include "transmitter/commandtransmitter.h"

#include "definition/sslmath.h"

using namespace std;

int main(int argc, char *argv[])
{
//    QApplication app(argc, argv);

//    double angle = -3*M_PI_4;
//    double start = 0;
//    cout << "for " << angle << " > "<< continuousRadian(angle, start) <<   endl;

    cout << "Main is running ... " << endl;

    SSLVision *vision = new SSLVision();
    vision->open(GRSIM_VISION_PORT);

    VisionFilter *filter =  VisionFilter::getInstance();

    SSLAnalyzer *analyzer = SSLAnalyzer::getInstance();

    SSLGame *game = SSLGame::getInstance(Yellow, Right);

    GUIHandler *gui = GUIHandler::getInstance();

    CommandTransmitter* transmitter = CommandTransmitter::getInstance();


    while (true)
    {
        vision->check();
        filter->check();
        analyzer->check();
        game->check();
        gui->check();
        transmitter->check();
        usleep(30000);
    }

    //    return app.exec();
    // ------------ test scripts -------------------


}

