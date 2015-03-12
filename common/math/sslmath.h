#ifndef SSLMATH_H
#define SSLMATH_H

#include <boost/date_time/posix_time/posix_time.hpp>
using namespace boost::posix_time;

namespace SSL {
    float continuousRadian(float angle, float start_ang);

    float minAngleDistToRange(float my_angle, float range_start, float range_end_);

    float uni_rand(float a, float b);

    double currentTimeMSec();

    template <typename T> int sgn(T val) {
        return (T(0) < val) - (val < T(0));
    }
}


#endif // SSLMATH_H
