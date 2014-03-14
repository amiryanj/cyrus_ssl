#include "sslmath.h"
#include <cmath>
#include <iostream>

double SSL::continuousRadian(double angle, double start_ang) {
    int counter = 0;
    if(fabs(angle) > 2* M_PI) {
        double c = angle/(2*M_PI);
        double d = floor(c) * (2*M_PI);
        angle = angle - d;
        if(fabs(angle) < 2*M_PI) {
            std::cout << "Error : continuous radian: angle = " << angle << std::endl;
        }
//        assert(fabs(angle) < 2*M_PI);
        std::cout << "Warning! teta of some parameter might be invalid (too large)." << std::endl;
    }
    while (angle < start_ang) {
        angle += 2 * M_PI;
        counter ++;
//        assert(counter < 3);
        if(counter > 5) {
            std::cout << "Invalid arguemnt in continuous radian computation" << std::endl;
            return 0;
        }
    }
    while (angle > start_ang + 2 * M_PI) {
        angle -= 2 * M_PI;
        counter ++;
//        assert(counter < 3);
        if(counter > 5) {
            std::cout << "Invalid arguemnt in continuous radian computation" << std::endl;
            return 0;
        }
    }
    return angle;
}

// compute the minimum rotation required to get a angel interval from a specific start angle
// start and end angles can be equal
double SSL::minAngleDistToRange(double my_angle, double range_start, double range_end_) {
    if(range_start == -INFINITY || range_end_ == INFINITY)
        return 0;
    my_angle = continuousRadian(my_angle, range_start);
    if(my_angle >= range_start && my_angle <= range_end_)
        return 0; // my_angle falls between start and end angle
    double t_s = range_start - my_angle;
    if(t_s < M_PI)
        t_s += 2*M_PI;
    if(t_s > M_PI)
        t_s += 2*M_PI;
    double t_e = range_end_ - my_angle;
    if(t_e < M_PI)
        t_e += 2*M_PI;
    if(t_e > M_PI)
        t_e += 2*M_PI;
    if(fabs(t_e) < fabs(t_s))
        return t_e;
    return t_s;
}

double SSL::uni_rand(double a, double b)
{
    double range = b - a;
    double r = ((double)rand() / (double)RAND_MAX) * range;
    return r + a;
}

double SSL::currentTimeMSec()
{
    ptime t1(microsec_clock::universal_time());
    time_duration td = t1.time_of_day();
    double time_ =  td.total_microseconds()/1000.0;
    return time_;
}
