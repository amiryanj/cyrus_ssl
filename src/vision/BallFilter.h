#ifndef _BALLFILTER_H
#define _BALLFILTER_H

#include "math/vector2d.h"
#include <vector>
#include "NaiveKalman.h"
#include "Frame.h"

#define MAX_BALL_MEMORY 30
#define MAX_BALL_MEDIAN_MEMORY 12
#define BALL_SPEED_LIMIT_FILTER 7

class BallFilter
{
public:
    BallFilter();

    void putNewFrame(const Frame &fr);

    // main method for updating state vectors
    void runFilter();

    Vector2D getUnfilteredSpeed() const;
    Vector2D getMedianFilteredSpeed() const;
    Vector2D getFilteredPosition() const;

private:
    std::vector<Frame> rawPositionList;
    Vector2D rawSpeedList[MAX_BALL_MEDIAN_MEMORY];
    double last_update_time_msec;
    double last_delta_t_sec;

    Vector2D m_filteredPosition;
    Vector2D m_unfilteredSpeed;
    Vector2D m_medianFilteredSpeed;

    NaiveKalman naiveFilter;

    int __medianFilterIndex;
};

#endif // _BALLFILTER_H
