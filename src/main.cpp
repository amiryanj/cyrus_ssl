//#include <QCoreApplication>
#include <QApplication>
#include <iostream>
#include <string>
#include "ai/SSLGame.h"
#include "vision/SSLVision.h"
#include "tools/vector3d.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    cerr << "Main is running ... " << endl;

    SSLVision *vision = new SSLVision();
    vision->open(GRSIM_VISION_PORT);
    while (true)
    {
        vision->check();
    }

    return app.exec();
}

