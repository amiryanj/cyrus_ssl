#include "ai/SSLGame.h"
#include "vision/SSLVision.h"
#include "referee/SSLReferee.h"
#include "general.h"
//#include <QVector3D>

#include "tools/stdlist.h"
#include "ai/SSLAnalyzer.h"
#include "gui/guihandler.h"
#include "transmitter/commandtransmitter.h"

#include "tools/sslmath.h"
using namespace std;

//******************************************************
#define OUR_COLOR   SSL::Blue
#define OUR_SIDE    SSL::Right
//******************************************************

int main(int argc, char *argv[])
{
//    QApplication app(argc, argv);

//    double angle = -3*M_PI_4;
//    double start = 0;
//    cout << "for " << angle << " > "<< continuousRadian(angle, start) <<   endl;

    cout << "Main is running ... " << endl;
    long loopCounter = 0;

    SSLReferee *referee = new SSLReferee(SSL_REFEREE_PORT, SSL_REFEREE_ADDRESS);

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
        vision->check();
        filter->check();
        analyzer->check();
        if((loopCounter % 5) ==0) {
            gameModule->check();
        }
        if(loopCounter % 25 == 0)  {
            gui->check();
            transmitter->check();
        }
        usleep(5000);
    }

//    RobotCommandPacket pkt;
//    pkt.setVelocity(0, 0, 0);
//    transmitter->send(0, pkt);
//    transmitter->check();

    //    return app.exec();
    // ------------ test scripts -------------------


}

