#ifndef _TESTMATHFUNCTIONS_H
#define _TESTMATHFUNCTIONS_H

#include <iostream>
#include "vector2d.h"
#include "vector3d.h"
#include "linesegment.h"
#include "sslmath.h"
#include "../soccer/sslgamepositions.h"
#include "../log-tools/networkplotter.h"
#include "../soccer/sslskill.h"

using namespace std;

// --------  test area ---------------
namespace Test {
bool testDistToLine()  {
    Vector2D p(0, 2);
    LineSegment l(0, 0, -1, -1);
    cout <<p.distToLine(l) << endl;
    exit(1);
}

bool testLineIntersection()  {
    LineSegment l1(-10, 4, 1, 4);
    LineSegment l2(2, -10, 2, 10);

    Vector2D intersection_point = LineSegment::intersection(l1, l2);
    printf("intersection test [%.6f, %.6f]\n", intersection_point.X(), intersection_point.Y());
    exit(1);
}

bool testNearestPointFromLine()  {
    LineSegment l1(10, -1, 10, 1);
    Vector2D pnt(-2, 0);

    Vector2D nearest_point = l1.nearestPointFrom(pnt);

    printf("Nearest point test [%.6f, %.6f]\n", nearest_point.X(), nearest_point.Y());
    exit(1);
}

bool testAimedPointfRobot()  {
    Vector2D result = SSL::Position::aimedPointOfRobot(Vector2D(-4500, 0), 5*M_PI/6.0);
    printf("Aimed Point of Robot test [%.6f, %.6f]\n", result.X(), result.Y());
    exit(1);
}

void testVelocityStrenght() {
    for (int i=0; i<1000; i++) {
        float result = SSLSkill::computeVelocityStrenghtbyDistance((double)i, 3000);
        NetworkPlotter::getInstance()->buildAndSendPacket("velocity coeff", result);
        usleep(3000);
    }
    exit(1);
}

}
// -------- ---------- ---------------

#endif // _TESTMATHFUNCTIONS_H
