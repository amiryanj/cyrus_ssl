#ifndef _STATION_H
#define _STATION_H

#include <cmath>
#include <iostream>
#include "../../shared/utility/vector3d.h"

typedef Vector3D Velocity;

class Station
{
public:
    Station(Vector3D position_ = Vector3D(INFINITY, INFINITY, INFINITY));

    struct StationCost {
        float min_ob_dist;
        float delta_heading;
        void setZero() {
            min_ob_dist = INFINITY;
            delta_heading = 0;
        }
        float safety_penalty() {
            min_ob_dist = std::max(min_ob_dist, 0.001f);
            return (1.0 / min_ob_dist) * 5.0;
        }
        float smooth_penalty() {
            return pow(fabs(delta_heading) /(M_PI /16.0), 2.0);
        }
        StationCost& operator =(const StationCost &other) {
            this->min_ob_dist = other.min_ob_dist;
            this->delta_heading = other.delta_heading;
            return *this;
        }
    } cost;

    void setPosition(const Vector3D &pos);
    Vector3D getPosition() const;

    void setVelocity(const Velocity &vel);
    Velocity getVelocity() const;

    bool isValid();

    void set(Station& other);
    void operator =(Station& other);
    bool operator ==(Station& other);

    void printToStream(std::ostream& stream);

    static float dubinDistance(const Station &from, const Station &to);
    static float euclideanDistance(const Station& from, const Station &to);

private:
    Vector3D position;
    Velocity velo;

};

#endif // _STATION_H
