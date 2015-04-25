#ifndef _STATION_H
#define _STATION_H

#include <cmath>
#include <iostream>
#include "../../shared/utility/vector3d.h"

typedef Vector3D Velocity;

class Station
{
public:
    Station(Vector3D position_ = Vector3D(INFINITY, INFINITY, INFINITY)) {
        mPosition = position_;
    }

    void setPosition(const Vector3D &pos_) {
        mPosition = pos_;
    }

    Vector3D getPosition() const {
        return mPosition;
    }

    void setVelocity(const Velocity &vel_) {
        mVelocity = vel_;
    }

    Velocity getVelocity() const {
        return mVelocity;
    }

    bool isValid() {
        if(mPosition.X() == INFINITY || mPosition.Y() == INFINITY || mPosition.Teta() == INFINITY)
            return false;
        return true;
    }

    void set(const Station& other) {
        (*this) = other;
    }

    void operator =(const Station& other);
    bool operator ==(const Station& other);

    void printToStream(std::ostream& stream);

    static float dubinDistance(const Station &from, const Station &to);
    static float euclideanDistance(const Station& from, const Station &to);

    struct StationCost {
        float min_dist_to_obs;
        float delta_heading;
        void setZero() {
            min_dist_to_obs = INFINITY;
            delta_heading = 0;
        }
        float safety_penalty() {
            min_dist_to_obs = std::max(min_dist_to_obs, 0.001f);
            return (1.0 / min_dist_to_obs) * 5.0;
        }
        float smooth_penalty() {
            return pow(fabs(delta_heading) /(M_PI /16.0), 2.0);
        }
        StationCost& operator =(const StationCost &other) {
            this->min_dist_to_obs = other.min_dist_to_obs;
            this->delta_heading = other.delta_heading;
            return *this;
        }
    } cost;

private:
    Vector3D mPosition;
    Velocity mVelocity;
};

#endif // _STATION_H
