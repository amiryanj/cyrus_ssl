#ifndef _SSLGAMEPOSITIONS_H
#define _SSLGAMEPOSITIONS_H

#include "../../common/math/vector2d.h"
#include "../../common/math/vector3d.h"
#include "../../common/math/linesegment.h"


namespace SSL {
namespace Position {

    Vector2D opponentPenaltyPoint();
    Vector2D ourPenaltyPoint();

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

    Vector3D goalKeeperPosition(float normalized_x_offset, float normalized_y_offset, const Vector2D &toward_point);

    LineSegment ourGoalLine();
    LineSegment opponentGoalLine();
    LineSegment HalfLine();
    LineSegment MidLine();

}
}


#endif // SSLGAMEPOSITIONS_H
