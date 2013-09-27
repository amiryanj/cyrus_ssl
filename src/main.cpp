//#include <QCoreApplication>
#include <QApplication>
#include <QDebug>
#include <iostream>
#include "ai/SSLGame.h"
#include "vision/SSLRobotKalmanFilter.h"
#include "thirdparty/serialib/serialib.h"
#include "vision/SSLVision.h"
#include "vision/frame.h"
#include <string>
#include "tools/vector3d.h"
#include <QUdpSocket>
#include "thirdparty/socket/netraw.h"

using namespace std;
using namespace Net;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    cerr << "Main is running ... " << endl;
    cout << "Main is running ... " << endl;

    SSLVision *vision = new SSLVision(GRSIM_VISION_PORT, GRSIM_VISION_ADDRESS);
    vision->open(GRSIM_VISION_PORT);
    while (true)
    {
        vision->check();
    }

    return app.exec();
}

