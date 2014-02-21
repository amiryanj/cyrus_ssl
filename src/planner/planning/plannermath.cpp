#include "plannermath.h"
#include <cstdlib>
#include <math.h>

#include <boost/date_time/posix_time/posix_time.hpp>
using namespace boost::posix_time;

double MyMath::uni_rand(double a, double b)
{
    double range = b - a;
    double r = ((double)rand() / (double)RAND_MAX) * range;
    return r + a;
}

double MyMath::currentTimeMSec()
{
    ptime t1(microsec_clock::universal_time());
    time_duration td = t1.time_of_day();
    double time_ =  td.total_microseconds()/1000.0;
    return time_;
}
