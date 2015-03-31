#ifndef _TESTGOTOPOINT_H
#define _TESTGOTOPOINT_H

#include "../../common/tools/SSLListener.h"
#include "../../math/vector3d.h"

class TestGoToPoint : public SSLListener
{
    Vector3D target[4];
    int i;
public:
    TestGoToPoint();

    void check();

};

#endif // _TESTGOTOPOINT_H
