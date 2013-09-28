#include "SSLObject.h"

SSLObject::SSLObject()
{
}

Vector3D SSLObject::Position() const
{
    return this->position_;
}

Vector3D SSLObject::Speed() const
{
    return this->speed_;
}

void SSLObject::setPosition(const Vector3D &position_)
{
    this->position_ = position_;
}

void SSLObject::setSpeed(const Vector3D &speed_)
{
    this->speed_ = speed_;
}
