#include "ai/SSLGame.h"
#include "vision/SSLVision.h"
#include "general.h"
#include <QVector3D>

#include "tools/stdlist.h"
#include "ai/SSLAnalyzer.h"
#include "gui/guihandler.h"

using namespace std;

int main(int argc, char *argv[])
{
//    QApplication app(argc, argv);

    cerr << "Main is running ... " << endl;

    SSLVision *vision = new SSLVision();
    vision->open(GRSIM_VISION_PORT);

    VisionFilter *filter =  VisionFilter::getInstance();

    SSLAnalyzer *analyzer = SSLAnalyzer::getInstance();

    SSLGame *game = SSLGame::getInstance(Yellow, Right);

    GUIHandler *gui = GUIHandler::getInstance();

//    Planner::RRTPlanner myPlanner;
//    myPlanner.agent;


    while (true)
    {
        vision->check();
        filter->check();
        analyzer->check();
        game->check();
        gui->check();
        usleep(500000);
    }

    //    return app.exec();
    // ------------ test scripts -------------------


}

