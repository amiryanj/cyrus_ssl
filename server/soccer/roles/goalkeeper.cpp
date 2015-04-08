#include "goalkeeper.h"
#include "../../../common/math/linesegment.h"
#include "../../definition/SSLTeam.h"
#include "../../definition/SSLRobot.h"
#include "../sslskill.h"
#include "../sslagent.h"

GoalKeeper::GoalKeeper()
{
    this->m_type = SSLRole::e_GoalKeeper;

    m_hardness = 0;
}

void GoalKeeper::run()
{
    // opponent penalty case
    // get ready
    if( analyzer->isOpponentPenaltyPosition() ) {
        Vector3D target = SSL::Position::coverGoalWithFixedDistance(50.0f, 0.0f, world->mainBall()->Position());
        m_agent->skill->goToPoint(target, SSLSkill::eAutoMove);
    }
    // show reaction
    else if(analyzer->isOpponentPenaltyKick()) {
        Vector3D target = SSL::Position::coverGoalWithFixedDistance(50.0f, 0.0f, world->mainBall()->Position());

        SSLAnalyzer::RobotIntersectTime op_penalty_kicker =
                analyzer->nearestRobotToPoint(game->opponentColor(), SSL::Position::ourPenaltyPoint());
        if(op_penalty_kicker.isValid())
        {
            float op_orien = op_penalty_kicker.m_robot->orien();
            Vector2D p1 = op_penalty_kicker.m_robot->Position().to2D();
            Vector2D p2 = p1 + Vector2D::unitVector(op_orien) * FIELD_LENGTH;

            LineSegment aim_line(p1, p2);
            LineSegment our_goal_line = SSL::Position::ourGoalLine();

            // the point where the penalty shooter aims to kick
            Vector2D aimed_point_by_penalty_shooter = LineSegment::intersection(aim_line, our_goal_line);
            if(aimed_point_by_penalty_shooter.X() < INFINITY)  {
                target = SSL::Position::coverGoalWithFixedDistance(30.0f,                // x_offset (mm)
                                                           aimed_point_by_penalty_shooter.Y(), // y_offset (mm)
                                                           world->mainBall()->Position());

            }
        }
        m_agent->skill->goToPoint(target, SSLSkill::eFastMove);
    }

    // check if the ball is coming toward our goal
    LineSegment ball_move_line(Ball_Position , Ball_Position + Ball_Speed * 4.0 /*seconds*/);
    Vector2D ball_intersection_with_goal_line =
            LineSegment::intersection(ball_move_line, SSL::Position::ourGoalLine());
    bool ball_is_coming_toward_our_goal = ( fabs(ball_intersection_with_goal_line.Y()) < FIELD_GOAL_WIDTH_2 * 2.5 );
                                                                                        // (with tolerance of 150%)
    if(ball_is_coming_toward_our_goal)
    {
        Vector3D target = SSL::Position::coverGoalWithOptimumDistance( this->myPosition() ,
                                                                       ball_intersection_with_goal_line.Y() ,
                                                                       Ball_Position );

        m_agent->skill->goToPoint(target, SSLSkill::eFastMove);
    }

    // ball is in penalty area
    else if(analyzer->isPointWithinOurPenaltyArea(world->mainBall()->Position())) {
        m_agent->skill->goAndKick(world->mainBall()->Position(),
                                  SSL::Position::opponentGoalCenter(),
                                  1); // goAndChip()
    }

    else {
        // normal play
        Vector2D risky_point = Ball_Position;
        float aimed_point_y = SSL::Position::ourGoalCenter().Y();

        SSLRobot* most_risky_opponent = 0;
        if(analyzer->isPointWithinOurCorner(world->mainBall()->Position())) {
            most_risky_opponent = analyzer->nearestToPoint(game->opponentTeam()->getInFieldRobots(),
                                                                     SSL::Position::ourGoalCenter());
        } else if(Ball_Speed.lenght() > 1000)  {// if the ball is not stable
            most_risky_opponent = analyzer->nearestToBall(game->opponentTeam()->getInFieldRobots());
        }
        if(most_risky_opponent != NULL) {
             risky_point = most_risky_opponent->Position().to2D();
             Vector2D aimed_point = SSL::Position::aimedPointOfRobot(most_risky_opponent->Position().to2D(),
                                                                     most_risky_opponent->orien() );
             aimed_point_y = bound(aimed_point.Y(), -FIELD_GOAL_WIDTH_2, FIELD_GOAL_WIDTH_2);
        }

        float dist_risky_point_from_goal = (risky_point - SSL::Position::ourGoalCenter()).lenght();
        Vector3D target = SSL::Position::coverGoalWithFixedRadius(FIELD_GOAL_WIDTH_2,
                                                                  aimed_point_y,
                                                                  risky_point);

        m_agent->skill->goToPoint(target, SSLSkill::eFastMove);
        return;
    }
}

Vector3D GoalKeeper::expectedPosition()
{
    return SSL::Position::ourGoalCenter().to3D();
}
