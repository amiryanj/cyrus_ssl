#ifndef _BALLFILTER_H
#define _BALLFILTER_H

#include "../tools/vector2d.h"
#include <vector>
#include "NaiveKalman.h"
#include "Frame.h"

#define MAX_BALL_MEMORY 30

class BallFilter
{
public:
    BallFilter();

    void putNewFrame(const Frame &fr);

    // main method for updating state vectors
    void runFilter();

    Vector2D getFilteredSpeed() const;
    Vector2D getFilteredPosition() const;

private:
    std::vector<Frame> rawPositionList;
    double last_update_time_msec;
    double last_delta_t_sec;

    Vector2D m_filteredPosition;
    Vector2D m_filteredSpeed;

    NaiveKalman naiveFilter;
};

#endif // _BALLFILTER_H
