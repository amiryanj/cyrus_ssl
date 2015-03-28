#ifndef _BALLFILTER_H
#define _BALLFILTER_H

#include <vector>
#include <stdlib.h>
#include "sslframe.h"
#include "alphabetafilter.h"
#include "../../common/math/vector2d.h"
#include "../definition/SSLBall.h"


#define MAX_BALL_MEMORY 13
#define MAX_BALL_MEDIAN_MEMORY 12
#define BALL_SPEED_LIMIT_FILTER 7

using namespace std;

class BallFilter
{
    friend class MainWindow;
    friend class GUIHandler;
    friend class VisionFilter;
public:
    BallFilter();

    void initialize(const SSLFrame &initial_frame);

    void putNewFrame(const SSLFrame &detected_ball);
    void putNewFrameWithManyBalls(vector<SSLFrame> detected_balls);

    // main method for updating state vectors
    void run();
    void executeAlphaBetaFilter();
    void executeClusterFilter();

    bool isEmpty() const;

protected:
    SSLBallState& getRawData(uint i) {return rawData[i];}
    vector<SSLBallState> rawData;

    bool getBallStoppedState();

    vector<SSLFrame> rawPositions;

    Vector2D m_rawPosition;
    Vector2D m_displacement;
    Vector2D m_filteredPosition;

    Vector2D m_clusteredVelocity;

    Vector2D m_rawVelocity;
    Vector2D m_filteredVelocity;

    Vector2D m_acceleration;

    AlphaBetaFilter alphaBetaFilter;



//    int __medianFilterIndex;
};

#endif // _BALLFILTER_H
