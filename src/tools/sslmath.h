#ifndef SSLMATH_H
#define SSLMATH_H

#include <boost/date_time/posix_time/posix_time.hpp>
using namespace boost::posix_time;

namespace SSL {
    double continuousRadian(double angle, double start_ang);

    double minAngleDistToRange(double my_angle, double range_start, double range_end_);

    double uni_rand(double a, double b);

    double currentTimeMSec();
}


#endif // SSLMATH_H
