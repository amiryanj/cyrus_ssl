#include "station.h"
#include <vector2d.h>
#include <sslmath.h>

Station::Station(Vector3D position_)
{
    this->position = position_;
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

Velocity Station::getVelocity() const
{
    return this->velo;
}

bool Station::isValid()
{
    if(position.X() == INFINITY || position.Y() == INFINITY || position.Teta() == INFINITY)
        return false;
    return true;
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
    this->cost = other.cost;
}

bool Station::operator ==(Station &other)
{
    if(this->position == other.position) // && this->velocity == other.velocity)
        return true;
    return false;
}

void Station::printToStream(std::ostream &stream)
{
    stream << "[Station]: X= " << position.X() << " ,Y= " << position.Y() << " ,Orien:" << position.Teta()
           << " Safety Cost:" << cost.safety_penalty() << ", Smooth Cost:" << fabs(cost.smooth_penalty())
           << std::endl ;
}

float Station::dubinDistance(const Station &from, const Station &to)
{
    float angle = (to.getPosition().to2D() - from.getPosition().to2D()).arctan();
    angle = SSL::continuousRadian(angle, from.getPosition().Teta() - M_PI);
    if(fabs(angle - from.getPosition().Teta()) > M_PI / 4.0)
        return INFINITY;
    return euclideanDistance(from, to);
}

float Station::euclideanDistance(const Station &from, const Station &to)
{
    return (to.getPosition() - from.getPosition()).lenght2D();
}
