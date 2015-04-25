#include "station.h"
#include <vector2d.h>
#include <generalmath.h>

void Station::operator =(const Station &other)
{
    this->mPosition  = other.mPosition;
    this->mVelocity      = other.mVelocity;
    this->cost      = other.cost;
}

bool Station::operator ==(const Station &other)
{
    if(this->mPosition == other.mPosition) // && this->velocity == other.velocity)
        return true;
    return false;
}

void Station::printToStream(std::ostream &stream)
{
    stream << "[Station]: X= " << mPosition.X() << " ,Y= " << mPosition.Y() << " ,Orien:" << mPosition.Teta()
           << " Safety Cost:" << cost.safety_penalty() << ", Smooth Cost:" << fabs(cost.smooth_penalty())
           << std::endl ;
}

float Station::dubinDistance(const Station &from, const Station &to)
{
    float angle = (to.getPosition().to2D() - from.getPosition().to2D()).arctan();
    angle = continuousRadian(angle, from.getPosition().Teta() - M_PI);
    if(fabs(angle - from.getPosition().Teta()) > M_PI / 4.0)
        return INFINITY;
    return euclideanDistance(from, to);
}

float Station::euclideanDistance(const Station &from, const Station &to)
{
    return (to.getPosition() - from.getPosition()).lenght2D();
}
