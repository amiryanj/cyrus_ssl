#ifndef _TESTMATHFUNCTIONS_H
#define _TESTMATHFUNCTIONS_H

#include <iostream>
#include "vector2d.h"
#include "vector3d.h"
#include "linesegment.h"
#include "generalmath.h"
#include "../soccer/sslgamepositions.h"
#include "../log-tools/networkplotter.h"
#include "../soccer/sslskill.h"
#include <Box2D/Collision/b2Collision.h>
#include <Box2D/Collision/b2Distance.h>
#include <Box2D/Collision/Shapes/b2EdgeShape.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>


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

void testContactShapes() {
    b2DistanceProxy a_proxy, b_proxy;
    b2CircleShape pa;
    pa.m_radius = FIELD_PENALTY_AREA_RADIUS;
    pa.m_p.Set(SSL::Position::ourGoalFocalPointTop().X(),
               SSL::Position::ourGoalFocalPointTop().Y());
    b2EdgeShape edge;
    edge.Set(b2Vec2(2000, 200), SSL::Position::ourGoalCenter().toB2vec2());
    a_proxy.Set(&pa  , 0);
    b_proxy.Set(&edge, 1);

    b2DistanceInput dist_in;
    dist_in.proxyA = a_proxy;
    dist_in.proxyB = b_proxy;
    dist_in.transformA = b2Transform();
    dist_in.transformB = b2Transform();
    b2SimplexCache dist_cache;
    dist_cache.count = 0;
    b2DistanceOutput dis_out;
    b2Distance(&dis_out, &dist_cache, &dist_in);
    b2Vec2 result = dis_out.pointB;


    printf("result: %.3f   %.3f \n", result.x, result.y);


    exit(1);

//    b2DistanceProxy state_proxy, ob_proxy;
//    state_proxy.Set(agent.shape, 0);
//    ob_proxy.Set(ob.shape, 1);
//    b2DistanceInput dist_in;
//    dist_in.proxyA = state_proxy;
//    dist_in.proxyB = ob_proxy;
//    dist_in.transformA = b2Transform(A.getPosition().toB2vec2(),
//                                    b2Rot(A.getPosition().Teta()));
//    dist_in.transformB = ob.m_transform;
//    b2SimplexCache dist_cache;
//    dist_cache.count = 0;
//    b2DistanceOutput dis_out;
//    b2Distance(&dis_out, &dist_cache, &dist_in);
//    A_point = dis_out.pointA;
//    ob_point = dis_out.pointB;
//    if(hasCollision(A, ob)) {
//        return -1;
//    }
//    return dis_out.distance;
}
//    return dis_out.distance;


}
// -------- ---------- ---------------

#endif // _TESTMATHFUNCTIONS_H
