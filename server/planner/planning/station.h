#ifndef STATE_H
#define STATE_H

#include "math/vector3d.h"
#include "velocity.h"
#include "iostream"

class Station
{
public:
    Station();

    void setPosition(const Vector3D &pos);
    Vector3D getPosition() const;

    void setVelocity(const Velocity &vel);
    Velocity getVelociy() const;

    Vector3D position;
    Velocity velo;

    bool isValid();

    void set(Station& other);
    void operator =(Station& other);
    bool operator ==(Station& other);

    void printToStream(std::ostream& stream);

};

#endif // STATE_H
