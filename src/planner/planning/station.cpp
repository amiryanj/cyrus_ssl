#include "station.h"
#include <cmath>

Station::Station()
{
    this->position.set(INFINITY, INFINITY, INFINITY);
}

void Station::setPosition(const Vector3D &pos)
{
    this->position = pos;
}

Vector3D Station::getPosition() const
{
    return this->position;
}

void Station::setVelocity(const Velocity &vel)
{
    this->velo = vel;
}

Velocity Station::getVelociy() const
{
    return this->velo;
}

bool Station::isValid()
{
    return (this->position != Vector3D(INFINITY, INFINITY, INFINITY));
}

void Station::set(Station &other)
{
    this->position = other.position;
    this->velo = other.velo;
}

void Station::operator =(Station &other)
{
    this->position = other.position;
    this->velo = other.velo;
}

bool Station::operator ==(Station &other)
{
    if(this->position == other.position) // && this->velocity == other.velocity)
        return true;
    return false;
}
