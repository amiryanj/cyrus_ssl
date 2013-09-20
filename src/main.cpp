//#include <QCoreApplication>
#include <QApplication>
#include <QDebug>
#include <iostream>
#include "ai/SSLGame.h"
#include "vision/SSLRobotKalmanFilter.h"
#include "thirdparty/serialib/serialib.h"
#include "vision/frame.h"
#include <string>
#include "tools/vector3d.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    cerr << "Main is running ... " << "\n";
    cerr << SSLGame::getInstance()->world->team[Yellow]->robot[3]->Position().x << endl;

//    SSLRobotKalmanFilter srkf_;
    frame fr1;
    frame fr2;
    qDebug() << fr1.timeTag;
    qDebug() << fr2.timeTag;

    Vector3D *vec1 = new Vector3D(12.4, 213.5, -23.5);
    Vector3D *vec2 = new Vector3D(12.4, 213.5, -23.5);
    (*vec1) += (*vec2);
    Vector2D vec3 = vec1->toVector2D();

    return app.exec();
}

