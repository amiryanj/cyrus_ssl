#ifndef SSLROBOTKALMANFILTER_H
#define SSLROBOTKALMANFILTER_H

#include <kalman/ekfilter.hpp>
#include "../general.h"

#include <Box2D/Common/b2Timer.h>

#include "frame.h"

//using namespace std;

#define MAX_RAW_DATA_MEMORY 30

class SSLRobotKalmanFilter : public Kalman::EKFilter<double, 1>
{
public:
    SSLRobotKalmanFilter();
    void setNewFrame(const frame &fr);
    bool isEmpty();
    bool isOnField();

    // main method for updating state vectors
    void runFilter();

    Vector3D getFilteredSpeed() const;
    Vector3D getFilteredPosition() const;

private:
    std::vector<frame> rawPositionList;
    double _last_update_time;
    double _last_interval_time;

    Vector3D filteredPosition;
    Vector3D filteredSpeed;

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
