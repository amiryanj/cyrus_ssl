#include "control.h"

Control::Control()
{
    Vx = Vy = Wz = 0;
}

void Control::operator =(Control &other)
{
    this->Vx = other.Vx;
    this->Vy = other.Vy;
    this->Wz = other.Wz;
}
