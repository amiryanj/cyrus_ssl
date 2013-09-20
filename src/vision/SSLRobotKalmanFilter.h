#ifndef SSLROBOTKALMANFILTER_H
#define SSLROBOTKALMANFILTER_H

#include <kalman/ekfilter.hpp>
#include "../general.h"
#include <QVector3D>
#include <list>
using namespace std;

#define MAX_RAW_DATA_MEMORY 30

class SSLRobotKalmanFilter : public Kalman::EKFilter<double, 1>
{
    typedef pair<time_msec, Vector3D> frame;

public:
    SSLRobotKalmanFilter();
    void setNewFrame(const time_msec &time_tag,const Vector3D &pose);
    bool isEmpty();
    bool isOnField();

    void runFilter();

    Vector3D filteredPosition;
    Vector3D filteredSpeed;

private:
    list<frame> rawPositionList;

protected:
    void makeA();
    void makeH();
    void makeV();
    void makeR();
    void makeW();
    void makeQ();
    void makeProcess();
    void makeMeasure();

};

//typedef SSLRobotKalmanFilter::Vector KFVector;
//typedef SSLRobotKalmanFilter::Matrix KFMatrix;

#endif // SSLROBOTKALMANFILTER_H
