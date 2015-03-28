#ifndef _SSLGAMEPOSITIONS_H
#define _SSLGAMEPOSITIONS_H

#include "../../common/math/vector2d.h"
#include "../../common/math/vector3d.h"


namespace SSL {
namespace Position {

    Vector2D opponentPenaltyPoint();
    Vector2D opponentGoalCenter();
    Vector2D ourGoalCenter();

    Vector3D ourMidfieldUpPosition();
    Vector3D ourMidfieldUpPosition();
    Vector3D ourMidfieldDownPosition();
    Vector3D opponentMidfieldUpPosition();
    Vector3D opponentMidfieldDownPosition();
    Vector3D midlineUpPosition();
    Vector3D midlineDownPosition();
    Vector3D wallStandFrontBall(int number, Vector2D ball_position);
    Vector3D KickStylePosition(const Vector2D &kick_point, const Vector2D &target, float dist);
    Vector3D DefenseStylePosition(const Vector2D &risky_point, const Vector2D &defense_point, float dist_from_risky);

}
}


#endif // SSLGAMEPOSITIONS_H
