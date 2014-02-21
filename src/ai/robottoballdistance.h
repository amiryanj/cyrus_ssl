#ifndef ROBOTTOBALLDISTANCE_H
#define ROBOTTOBALLDISTANCE_H

#include "../definition/Concepts.h"
#include "../definition/SSLRobot.h"
#include "../definition/SSLBall.h"

/*
 * @author : Javad
 * In this class all time units are : "second"
 */

class RobotDistTo
{
public:
    RobotDistTo(const SSLRobot* rob, const SSLBall* bal);

    const SSLRobot* robot;

    static const SSLBall* ball; // main Ball

    static double minTimeToBall; // in second
    static const SSLRobot* nearestRobotToBall;

    static double minTimeToBallOfTeam[2];
    static const SSLRobot* nearestRobotToBallOfTeam[2];

    static double distToPoint(SSLRobot* robot, const Vector2D &point);

    double getEuclideanTimeToBallSec() const;
    double getManifoldTimeToBallSec() const;
    Vector2D getBallInstersectPoint() const;

    void computeEuclideanToBall();
    void computeManifoldToBall();

private:
    double euclideanDistB; // unit: ?
    double euclideanTimeB; // unit: second

    double onManifoldDistB; // unit: ?
    double onManifoldTimeB; // unit: second
    Vector2D intersectPointB;

};

#endif // ROBOTTOBALLDISTANCE_H
