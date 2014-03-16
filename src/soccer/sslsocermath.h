#ifndef SSLSOCERMATH_H
#define SSLSOCERMATH_H

#include "../tools/vector2d.h"
#include "../definition/SSLRobot.h"
#include <math.h>
#include "../ai/SSLGame.h"

class SSLSocerMath
{
public:
    static float getFacingToPoint(const Vector2D& myPosition, const Vector2D& target);

    static bool isRobotOutsideOfDefenceArea(const Vector2D&, SSL::Side side);

    static bool isRobotFacingToEnemy(float facing, SSL::Side enemySide);

    static Vector2D getGoalPosition(SSL::Side side);

    static Vector2D getBlockPosition(Vector2D offenserPos, Vector2D blockedTargetPos, int numberofBlockers, int indexOfThisDefencer, float radius);

private:
};

#endif // SSLSOCERMATH_H
