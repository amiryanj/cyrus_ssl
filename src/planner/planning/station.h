#ifndef STATE_H
#define STATE_H

#include "tools/vector3d.h"
#include "control.h"

class Station
{
public:
    Station();

    void setPosition(const Vector3D &pos);
    Vector3D getPosition() const;

    Vector3D position;
    Control control;

    bool isValid();

    void set(Station& other);
    void operator =(Station& other);
    bool operator ==(Station& other);

};

#endif // STATE_H
