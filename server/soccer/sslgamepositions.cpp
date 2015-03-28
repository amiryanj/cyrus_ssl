#include "sslgamepositions.h"

#include "../ai/SSLGame.h"

namespace SSL{
namespace Position {

Vector2D opponentPenaltyPoint()
{
    return Vector2D(game->opponentSide() * (FIELD_LENGTH/2 - FIELD_PENALTY_DISTANCE), 0);
}

Vector2D opponentGoalCenter()
{
    return Vector2D(game->opponentSide() * (FIELD_LENGTH/2), 0);
}

Vector2D ourGoalCenter()
{
    return Vector2D(game->ourSide() * (FIELD_LENGTH/2), 0);
}

Vector3D ourMidfieldUpPosition()
{
    float x_ = game->ourSide() * (FIELD_LENGTH / 4) * 1.3;
    Vector2D point(x_, +600);
    return KickStylePosition(point, opponentGoalCenter(), 0);
}

Vector3D ourMidfieldCenterPosition()
{
    float x_ = game->ourSide() * (FIELD_LENGTH / 4) * 1.3;
    Vector2D point(x_, 0);
    return KickStylePosition(point, opponentGoalCenter(), 0);
}

Vector3D ourMidfieldDownPosition()
{
    float x_ = game->ourSide() * (FIELD_LENGTH / 4) * 1.3;
    Vector2D point(x_, -600);
    return KickStylePosition(point, opponentGoalCenter(), 0);
}

Vector3D opponentMidfieldUpPosition()
{
    float x_ = game->opponentSide() * (FIELD_LENGTH / 4);
    Vector2D point(x_, +900);
    return KickStylePosition(point, opponentGoalCenter(), 0);
}

Vector3D opponentMidfieldDownPosition()
{
    float x_ = game->opponentSide() * (FIELD_LENGTH / 4);
    Vector2D point(x_, -900);
    return KickStylePosition(point, opponentGoalCenter(), 0);
}

Vector3D midlineUpPosition()
{
    Vector2D point(0, 700);
    return KickStylePosition(point, opponentGoalCenter(), 0);
}

Vector3D midlineDownPosition()
{
    Vector2D point(0, 700);
    return KickStylePosition(point, opponentGoalCenter(), 0);
}

Vector3D wallStandFrontBall(int number, Vector2D ball_position)
{
    Vector2D def_point = ourGoalCenter();
    switch(number) {
    case -1:
        def_point.setY(-FIELD_GOAL_WIDTH * 0.8);
    case 0:
        def_point.setY(0);
    case 1:
        def_point.setY(FIELD_GOAL_WIDTH * 0.8);
    default:
        def_point.setY(FIELD_GOAL_WIDTH * 0.8);
    }

    return DefenseStylePosition(ball_position, def_point, 500);
}

Vector3D KickStylePosition(const Vector2D &kick_point, const Vector2D &target, float dist)
{
    Vector2D dir = (target - kick_point).normalized();
    float orien = dir.arctan();
    Vector3D pos(kick_point - dir * (BALL_RADIUS + ROBOT_RADIUS + dist), orien);
    return pos;
}

Vector3D DefenseStylePosition(const Vector2D &risky_point, const Vector2D &defense_point, float dist_from_risky)
{
    Vector2D dir = (risky_point - defense_point).normalized();
    float orien = dir.arctan();
    Vector3D pos(risky_point - dir * (dist_from_risky + ROBOT_RADIUS), orien);
    return pos;
}

}
}

