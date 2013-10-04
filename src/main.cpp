//#include <QApplication>
#include "ai/SSLGame.h"
#include "vision/SSLVision.h"
#include "general.h"

using namespace std;

int main(int argc, char *argv[])
{
//    QApplication app(argc, argv);

    cerr << "Main is running ... " << endl;

    SSLVision *vision = new SSLVision();
    vision->open(GRSIM_VISION_PORT);
    while (true)
    {
        vision->check();
        VisionFilterModule::getInstance()->check();
    }

//    return app.exec();
}

