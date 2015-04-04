#ifndef _SSLGAMEPOSITIONS_H
#define _SSLGAMEPOSITIONS_H

#include "../ai/SSLGame.h"
#include "../../common/math/vector2d.h"
#include "../../common/math/vector3d.h"
#include "../../common/math/linesegment.h"


namespace SSL {
namespace Position {

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

    Vector3D coverGoalWithFixedDistance(float x_offset, float covered_point_y, const Vector2D &shoot_point);
    Vector3D coverGoalWithFixedRadius(float radius_from_center, float covered_point_y, const Vector2D &shoot_point);
    Vector3D coverGoalWithOptimumDistance(Vector3D my_position, float covered_point_y, const Vector2D &shoot_point);

    float seePointOrientation(const Vector2D &my_position, const Vector2D & aimed_point);
    Vector2D aimedPointOfRobot(const Vector2D &Position, float orien);

    Vector2D opponentPenaltyPoint();
    Vector2D ourPenaltyPoint();
    Vector2D opponentGoalCenter();
    Vector2D ourGoalCenter();
    Vector2D ourGoalEdgeTop();
    Vector2D ourGoalEdgeDown();
    Vector2D opponentGoalEdgeTop();
    Vector2D opponentGoalEdgeDown();
    LineSegment ourGoalLine();
    LineSegment opponentGoalLine();
    LineSegment HalfLine();
    LineSegment MidLine();

}
}


#endif // SSLGAMEPOSITIONS_H
