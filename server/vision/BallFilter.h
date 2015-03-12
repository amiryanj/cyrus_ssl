#ifndef _BALLFILTER_H
#define _BALLFILTER_H

#include "../../common/math/vector2d.h"
#include <vector>
#include "NaiveKalman.h"
#include "Frame.h"

#define MAX_BALL_MEMORY 13
#define MAX_BALL_MEDIAN_MEMORY 12
#define BALL_SPEED_LIMIT_FILTER 7

using namespace std;

struct BallKinematic {
    double timeStamp_second; // variable unit = second  : SSSS.mmm
    Vector2D position; // mili meter
    Vector2D displacement; // mili meter
    Vector2D velocity; // mili meter per second
    Vector2D acceleration; // mili meter per second^2
    float turnInDegree() const {return acceleration.arctan() * 180.0/M_PI;}
//    bool hasSuddenChange() const {return ((acceleration.lenght() > )
//                                          || turnInDegree());}
};

class BallFilter
{
    friend class MainWindow;
public:
    BallFilter();

    void putNewFrame(const Frame &fr);
    void putNewFrameWithManyBalls(vector<Frame> balls_);

    // main method for updating state vectors
    void runFilter();

    Vector2D getFilteredSpeed() const;
    Vector2D getUnfilteredSpeed() const;
    Vector2D getFilteredPosition() const;
    Vector2D getAcceleration() const;
    Vector2D getDisplacement() const;

protected:
    BallKinematic& getRawData(uint i) {return rawData[i];}
    vector<BallKinematic> rawData;

    bool getBallStoppedState();

    vector<Frame> rawPositions;

    Vector2D rawSpeeds[MAX_BALL_MEDIAN_MEMORY];
    Vector2D rawAccelerations;

    Vector2D m_rawPosition;
    Vector2D m_displacement;
    Vector2D m_filteredPosition;

    Vector2D m_rawVelocity;
    Vector2D m_filteredVelocity;

    Vector2D m_accleration;

    NaiveKalman naiveFilter;

//    int __medianFilterIndex;
};

#endif // _BALLFILTER_H
