#include "sslmath.h"
#include <cmath>

double continuousRadian(double angle, double start_ang) {
    while (angle < start_ang) {
        angle += 2 * M_PI;
    }
    while (angle > start_ang + 2 * M_PI) {
        angle -= 2 * M_PI;
    }
    return angle;
}

