#ifndef _TESTMATHFUNCTIONS_H
#define _TESTMATHFUNCTIONS_H

#include "vector2d.h"
#include "vector3d.h"
#include "linesegment.h"
#include "sslmath.h"
#include "iostream"

using namespace std;

// --------  test area ---------------
namespace Test {
bool testDistToLine() {
    Vector2D p(0, 2);
    LineSegment l(0, 0, -1, -1);
    cout <<p.distToLine(l) << endl;

}

}
// -------- ---------- ---------------

#endif // _TESTMATHFUNCTIONS_H
