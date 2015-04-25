#include "randomsampling.h"
#include <cmath>
#include <stdlib.h>

Vector2D randomSampleFromRect(const Vector2D &p1, const Vector2D &p2)
{
    float x_ = uni_rand(p1.X(), p2.X());
    float y_ = uni_rand(p1.Y(), p2.Y());
    return Vector2D(x_, y_);
}

Vector2D randomSampleFromCircle(const Vector2D &center, float radius)
{
    float r = uni_rand(0, radius);
    float a = uni_rand(-M_PI, M_PI);
    return Vector2D(center.X() + r * cos(a), center.Y() + r * sin(a));
}

Vector2D randomSampleFromEllipse(const Vector2D &fp1, const Vector2D &fp2, float major_diameter)
{
    float foci_dist = (fp1 - fp2).lenght();
    float minor_diameter = sqrt(pow(major_diameter, 2) - pow(foci_dist, 2));
    float normal_radius = uni_rand(0, 1);
    float alfa = uni_rand(-M_PI, M_PI);

    float dx_ = (major_diameter/2.0) * normal_radius * cos(alfa);
    float dy_ = (minor_diameter/2.0) * normal_radius * sin(alfa);

    Vector2D disp_vec(dx_, dy_);
    disp_vec.rotate((fp1 - fp2).arctan());
    return Vector2D (fp1 + fp2) /2.0 + disp_vec;
}

float uni_rand(float a, float b)
{
    float range = b - a;
    float r = ((float)rand() / (float)RAND_MAX) * range;
    return r + a;
}


