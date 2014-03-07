#ifndef SSLROBOTKALMANFILTER_H
#define SSLROBOTKALMANFILTER_H

#include <kalman/ekfilter.hpp>
#include "../general.h"

#include <Box2D/Common/b2Timer.h>
#include "naivekalmanfilter.h"

#include "frame.h"

//using namespace std;

#define MAX_RAW_DATA_MEMORY 30

class SSLRobotKalmanFilter //: public Kalman::EKFilter<double, 1>
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
    double last_update_time_msec;
    double last_interval_time_sec;

    Vector3D filteredPosition;
    Vector3D filteredSpeed;

    static int state_size;
    static int observe_size;
    static int measure_noise_size;
    static int process_noise_size;

    NaiveKalmanFilter naiveFilter;
//    KalmanVector state;


protected:

//    void makeBaseA();
    void makeBaseV();
    void makeBaseR();
    void makeBaseW();
    void makeBaseQ();

    void makeA();
    void makeH();
    void makeProcess();
    void makeMeasure();

};

//typedef SSLRobotKalmanFilter::Vector KFVector;
//typedef SSLRobotKalmanFilter::Matrix KFMatrix;

#endif // SSLROBOTKALMANFILTER_H
