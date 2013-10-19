#include "ai/SSLGame.h"
#include "vision/SSLVision.h"
#include "general.h"
#include <QMap>
#include <QVector3D>

using namespace std;

int main(int argc, char *argv[])
{
//    QApplication app(argc, argv);

    cerr << "Main is running ... " << endl;

    SSLVision *vision = new SSLVision();
    vision->open(GRSIM_VISION_PORT);

    SSLGame *game = SSLGame::getInstance(Yellow, Right);
    while (true)
    {
        vision->check();
        VisionFilterModule::getInstance()->check();
        game->check();
    }

    //    return app.exec();
    // ------------ test scripts -------------------


}

