#ifndef SSLROBOTKALMANFILTER_H
#define SSLROBOTKALMANFILTER_H

#include <kalman/ekfilter.hpp>
#include "../general.h"
#include <list>
#include "frame.h"

using namespace std;

#define MAX_RAW_DATA_MEMORY 30

class SSLRobotKalmanFilter : public Kalman::EKFilter<double, 1>
{
public:
    SSLRobotKalmanFilter();
    void setNewFrame(const frame &fr);
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
