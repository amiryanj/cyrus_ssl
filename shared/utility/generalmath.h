#ifndef _GENERAL_MATH_H
#define _GENERAL_MATH_H


template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}

float continuousRadian(float angle, float start_ang);

// compute the minimum rotation required to get a angel interval from a specific start angle
// start and end angles can be equal
float minimumRequiredRotationToReachAngleRange(float my_angle, float range_start, float range_end_);

double currentTimeMSec();

float bound(float val_, float min_, float max_);

float sigmoid(float val_, float min_, float max_);

#endif // _GENERAL_MATH_H
