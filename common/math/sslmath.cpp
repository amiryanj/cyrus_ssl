#include "sslmath.h"
#include <cmath>
#include <iostream>

float SSL::continuousRadian(float angle, float start_ang) {
    int counter = 0;
    if(fabs(angle) > 2* M_PI) {
        float c = angle/(2*M_PI);
        float d = floor(c) * (2*M_PI);
        angle = angle - d;
        if(fabs(angle) > 2*M_PI) {
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
float SSL::minAngleDistToRange(float my_angle, float range_start, float range_end_) {
    if(range_start == -INFINITY || range_end_ == INFINITY)
        return 0;

    my_angle = continuousRadian(my_angle, range_start - M_PI);
    if(my_angle >= range_start && my_angle <= range_end_)
        return 0; // my_angle falls between start and end angle
    float t_s = range_start - my_angle;
//    if(t_s < -M_PI)
//        t_s += 2*M_PI;
//    if(t_s > M_PI)
//        t_s += 2*M_PI;
    my_angle = continuousRadian(my_angle, range_end_ - M_PI);
    float t_e = range_end_ - my_angle;
//    if(t_e < -M_PI)
//        t_e += 2*M_PI;
//    if(t_e > M_PI)
//        t_e += 2*M_PI;
    if(fabs(t_e) < fabs(t_s))
        return t_e;
    return t_s;
}

float SSL::uni_rand(float a, float b)
{
    float range = b - a;
    float r = ((float)rand() / (float)RAND_MAX) * range;
    return r + a;
}

double SSL::currentTimeMSec()
{
    ptime t1(microsec_clock::universal_time());
    time_duration td = t1.time_of_day();    
    double time =  (double) td.total_microseconds();
    time /= 1000.0f;
    return time;
}
