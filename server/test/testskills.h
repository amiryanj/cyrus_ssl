#ifndef _TESTSKILLS_H
#define _TESTSKILLS_H

#include "../../shared/tools/ssllistener.h"
#include "../../shared/utility/vector3d.h"
#include "../soccer/sslagent.h"

class TestSkills
{
    Vector3D target[4];
    int targetIndex;
public:
    TestSkills();

    void testGotoPoint();
    void testGotoBallDefense();
    void testKickBall();

    SSLAgent* agent;

};

#endif // _TESTSKILLS_H
