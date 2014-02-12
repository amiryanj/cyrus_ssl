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

bool Station::isValid()
{
    return (this->position != Vector3D(INFINITY, INFINITY, INFINITY));
}

void Station::set(Station &other)
{
    this->position = other.position;
    this->control = other.control;
}

void Station::operator =(Station &other)
{
    this->position = other.position;
    this->control = other.control;
}

bool Station::operator ==(Station &other)
{
    if(this->position == other.position) // && this->control == other.control)
        return true;
    return false;
}
