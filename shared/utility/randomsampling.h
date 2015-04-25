#ifndef _RANDOM_SAMPLING_H
#define _RANDOM_SAMPLING_H

#include "vector2d.h"

Vector2D randomSampleFromRect(const Vector2D &p1, const Vector2D &p2);
Vector2D randomSampleFromCircle(const Vector2D &center, float radius);
Vector2D randomSampleFromEllipse(const Vector2D &fp1, const Vector2D &fp2, float major_diameter);

float uni_rand(float a, float b);


#endif // _RANDOM_SAMPLING_H
