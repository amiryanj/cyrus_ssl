#ifndef _BALLFILTER_H
#define _BALLFILTER_H

#include <vector>
#include <cmath>
#include <math.h>
#include <stdlib.h>
#include "sslframe.h"
#include "alphabetafilter.h"
#include "../../common/math/vector2d.h"


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
    friend class GUIHandler;
    friend class VisionFilter;
public:
    BallFilter();

    void initialize(const SSLFrame &first_frame);

    void putNewFrame(const SSLFrame &detected_ball);
    void putNewFrameWithManyBalls(vector<SSLFrame> detected_balls);

    // main method for updating state vectors
    void run();

    bool isEmpty() const;

protected:
    BallKinematic& getRawData(uint i) {return rawData[i];}
    vector<BallKinematic> rawData;

    bool getBallStoppedState();

    vector<SSLFrame> rawPositions;

    Vector2D m_rawPosition;
    Vector2D m_displacement;
    Vector2D m_filteredPosition;

    Vector2D m_rawVelocity;
    Vector2D m_filteredVelocity;

    Vector2D m_acceleration;

    AlphaBetaFilter alphaBetaFilter;



//    int __medianFilterIndex;
};

#endif // _BALLFILTER_H
