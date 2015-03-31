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
bool testDistToLine()  {
    Vector2D p(0, 2);
    LineSegment l(0, 0, -1, -1);
    cout <<p.distToLine(l) << endl;

}

bool testLineIntersection()  {
    LineSegment l1(-10, 4, 10, 4);
    LineSegment l2(2, -10, 2, 10);

    Vector2D intersection_point = LineSegment::intersection(l1, l2);
    printf("intersection test [%.3f, %.3f]\n", intersection_point.X(), intersection_point.Y());
}

}
// -------- ---------- ---------------

#endif // _TESTMATHFUNCTIONS_H
