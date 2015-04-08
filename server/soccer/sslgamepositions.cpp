#include "sslgamepositions.h"

namespace SSL{
namespace Position {

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

float seePointOrientation(const Vector2D &my_position, const Vector2D & aimed_point)
{
    return continuousRadian((aimed_point - my_position).arctan(), -M_PI);
}

Vector2D aimedPointOfRobot(const Vector2D &Position, float orien)
{
    float x_ = ourGoalCenter().X();
    if( ((fabs(orien) - M_PI_2) * x_) > 0 )
        return Vector2D(x_, sgn(orien) * INFINITY);
    float dy_ = tan(orien) * fabs(Position.X() - x_) * -1.0 * sgn(fabs(orien) - M_PI_2);
    return Vector2D(x_, dy_ + Position.Y());
}

Vector3D coverGoalWithFixedDistance(float x_offset, float covered_point_y, const Vector2D &shoot_point)
{
    float x_pos = game->ourSide() *(FIELD_LENGTH_2 -ROBOT_RADIUS - x_offset);

//    covered_point_y = bound(covered_point_y, ROBOT_RADIUS-FIELD_GOAL_WIDTH/2, -ROBOT_RADIUS+FIELD_GOAL_WIDTH/2 );

    LineSegment vertical_line(x_pos ,-FIELD_WIDTH_2,
                              x_pos , FIELD_WIDTH_2 );

    LineSegment goal_top_edge_shoot_line(shoot_point, ourGoalEdgeTop());
    LineSegment goal_down_edge_shoot_line(shoot_point, ourGoalEdgeDown());

    float max_allowed_y = LineSegment::intersection(vertical_line, goal_top_edge_shoot_line).Y();
    float min_allowed_y = LineSegment::intersection(vertical_line, goal_down_edge_shoot_line).Y();

    LineSegment shoot_line(shoot_point,
                           Vector2D(game->ourSide() * FIELD_LENGTH_2, covered_point_y));
    float best_y_for_catch = LineSegment::intersection(vertical_line, shoot_line).Y();
    best_y_for_catch = bound(best_y_for_catch,
                             min_allowed_y + ROBOT_RADIUS + BALL_RADIUS,
                             max_allowed_y - ROBOT_RADIUS - BALL_RADIUS);

    float orien = (shoot_point - Vector2D(x_pos, best_y_for_catch)).arctan();
    return Vector3D(x_pos, best_y_for_catch, continuousRadian(orien, -M_PI));
}

Vector3D coverGoalWithFixedRadius(float radius_from_center, float covered_point_y, const Vector2D &shoot_point)
{
    Vector2D aimed_pnt(ourGoalCenter().X(), covered_point_y);
    Vector2D best_point = aimed_pnt + (shoot_point - aimed_pnt).normalized() * radius_from_center;

    LineSegment vertical_line(best_point.X() ,-FIELD_WIDTH_2,
                              best_point.X() , FIELD_WIDTH_2 );

    LineSegment goal_top_edge_shoot_line(shoot_point, ourGoalEdgeTop());
    LineSegment goal_down_edge_shoot_line(shoot_point, ourGoalEdgeDown());

    float max_allowed_y = LineSegment::intersection(vertical_line, goal_top_edge_shoot_line).Y();
    float min_allowed_y = LineSegment::intersection(vertical_line, goal_down_edge_shoot_line).Y();

    LineSegment shoot_line(shoot_point,
                           Vector2D(game->ourSide() * FIELD_LENGTH_2, covered_point_y));
    float best_y_for_catch = LineSegment::intersection(vertical_line, shoot_line).Y();
    best_y_for_catch = bound(best_y_for_catch,
                             min_allowed_y + ROBOT_RADIUS + BALL_RADIUS,
                             max_allowed_y - ROBOT_RADIUS - BALL_RADIUS);
    best_y_for_catch = bound( best_y_for_catch ,
                             -FIELD_GOAL_WIDTH_2 - ROBOT_RADIUS,
                              FIELD_GOAL_WIDTH_2 - ROBOT_RADIUS );

    float orien = (shoot_point - Vector2D(best_point.X(), best_y_for_catch)).arctan();
    return Vector3D(best_point.X(), best_y_for_catch, continuousRadian(orien, -M_PI));
}

// fast reation to opponent shoots, get the nearest position to save goal
Vector3D coverGoalWithOptimumDistance(Vector3D my_position, float covered_point_y, const Vector2D &shoot_point)
{
    /// not tested yet
//    assert(0);
    // limit this area to goal width
    covered_point_y = bound( covered_point_y,
                            -FIELD_GOAL_WIDTH_2 + ROBOT_RADIUS + BALL_RADIUS,
                             FIELD_GOAL_WIDTH_2 - ROBOT_RADIUS - BALL_RADIUS );
    LineSegment shoot_line(shoot_point,
                           Vector2D(game->ourSide() * FIELD_LENGTH_2, covered_point_y));
    float prependicular_line_slope = shoot_line.slope() + M_PI_2;
    LineSegment prependicular_line( my_position.to2D() - Vector2D::unitVector(prependicular_line_slope) * 100000.0,
                                    my_position.to2D() + Vector2D::unitVector(prependicular_line_slope) * 100000.0 );

    Vector2D catch_ball_pos = LineSegment::intersection(shoot_line, prependicular_line);
    catch_ball_pos.setY(bound(catch_ball_pos.Y(),
                             -FIELD_GOAL_WIDTH_2 - ROBOT_RADIUS,
                              FIELD_GOAL_WIDTH_2 + ROBOT_RADIUS));
    if(catch_ball_pos.X() < INFINITY) {
        return Vector3D(catch_ball_pos, my_position.Teta());
    }
    return my_position;

}

Vector2D opponentPenaltyPoint() {
    return Vector2D(game->opponentSide() * (FIELD_LENGTH/2 - FIELD_PENALTY_DISTANCE), 0);
}

Vector2D ourPenaltyPoint() {
    return Vector2D(game->ourSide() * (FIELD_LENGTH/2 - FIELD_PENALTY_DISTANCE), 0);
}

Vector2D opponentGoalCenter()  {
    return Vector2D(game->opponentSide() * (FIELD_LENGTH/2), 0);
}

Vector2D ourGoalCenter()  {
    return Vector2D(game->ourSide() * (FIELD_LENGTH/2), 0);
}

Vector2D ourGoalFocalPointTop() {
    return Vector2D(game->ourSide() * FIELD_LENGTH_2, FIELD_GOAL_WIDTH/4.0);
}

Vector2D ourGoalFocalPointDown() {
    return Vector2D(game->ourSide() * FIELD_LENGTH_2, -FIELD_GOAL_WIDTH/4.0);
}

Vector2D opponenetGoalFocalPointTop() {
    return Vector2D(game->opponentSide() * FIELD_LENGTH_2, FIELD_GOAL_WIDTH/4.0);
}

Vector2D opponenetGoalFocalPointDown() {
    return Vector2D(game->opponentSide() * FIELD_LENGTH_2, -FIELD_GOAL_WIDTH/4.0);
}

Vector2D ourGoalEdgeTop()  {
    return Vector2D(game->ourSide() * (FIELD_LENGTH/2), FIELD_GOAL_WIDTH_2);
}

Vector2D ourGoalEdgeDown()  {
    return Vector2D(game->ourSide() * (FIELD_LENGTH/2), -FIELD_GOAL_WIDTH_2);
}

Vector2D opponentGoalEdgeTop()  {
    return Vector2D(game->opponentSide() * (FIELD_LENGTH/2), FIELD_GOAL_WIDTH_2);
}

Vector2D opponentGoalEdgeDown()  {
    return Vector2D(game->opponentSide() * (FIELD_LENGTH/2), -FIELD_GOAL_WIDTH_2);
}

LineSegment ourGoalLine() {
    return LineSegment(game->ourSide() * FIELD_LENGTH/2, -FIELD_WIDTH/2,
                       game->ourSide() * FIELD_LENGTH/2,  FIELD_WIDTH/2);
}

LineSegment opponentGoalLine() {
    return LineSegment(game->opponentSide() * FIELD_LENGTH/2, -FIELD_WIDTH/2,
                       game->opponentSide() * FIELD_LENGTH/2,  FIELD_WIDTH/2);
}

LineSegment HalfLine() {
    return LineSegment(0, -FIELD_WIDTH/2,
                       0,  FIELD_WIDTH/2);
}

LineSegment MidLine() {
    return LineSegment(-FIELD_LENGTH/2, 0,
                        FIELD_LENGTH/2, 0);
}

}
}

