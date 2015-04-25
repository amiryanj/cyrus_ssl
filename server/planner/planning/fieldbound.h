#ifndef _FIELDBOUND_H
#define _FIELDBOUND_H

#include "vector3d.h"

class FieldBound
{
public:
    FieldBound()  {}
    virtual Vector3D getUniformSample() = 0;
    virtual bool isEmpty() = 0;
};



#endif // FIELDBOUND_H
