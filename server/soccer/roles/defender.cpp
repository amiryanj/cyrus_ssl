#include "defender.h"
#include "../sslagent.h"

Defender::Defender(int ind, int count)
{
    this->m_type = SSLRole::e_Defender;
    m_defenderCount = count;
    m_defenderIndex = ind;

    assert(ind <= count);

    m_hardness = 2;
}

Vector3D Defender::expectedPosition()
{
    Vector2D risky_point = Ball_Position;
    Vector2D cntr;
    float radius;
    Vector2D target;

    if(fabs(risky_point.Y()) < FIELD_PENALTY_AREA_WIDTH_2) {
        cntr = SSL::Position::ourGoalCenter();
        radius = FIELD_PENALTY_AREA_RADIUS * 1.1; Vector2D dist_vec = (risky_point - cntr).normalized() * (radius +ROBOT_RADIUS);
        if(m_defenderIndex == 2) {
            dist_vec.rotate(sgn(risky_point.Y()) * ROBOT_RADIUS / radius);
        }
        else {
            dist_vec.rotate(sgn(risky_point.Y()) * -1.0 * ROBOT_RADIUS / radius);
        }
        target = cntr + dist_vec;
    }
    else
    {
        if(risky_point.Y() > 0) {
            cntr = SSL::Position::ourGoalFocalPointTop();
        } else {
            cntr = SSL::Position::ourGoalFocalPointDown();
        }

        if((risky_point - SSL::Position::ourGoalCenter()).lenght() > FIELD_LENGTH_2) {
            radius = FIELD_PENALTY_AREA_RADIUS * 1.4;
        } else {
            radius = FIELD_PENALTY_AREA_RADIUS * 1.05;
        }

        Vector2D dist_vec = (risky_point - cntr).normalized() * (radius +ROBOT_RADIUS);
        if(m_defenderIndex == 2) {
            dist_vec.rotate(sgn(risky_point.Y()) * 2 * ROBOT_RADIUS / radius);
        }
        target = cntr + dist_vec;
    }


    return Vector3D(target, SSL::Position::seePointOrientation(target, risky_point));


//    float x = (float)(m_defenderCount + 1)/2.0;
//    float displaceAngle = (m_defenderIndex - x) * (1.6 *ROBOT_RADIUS /FIELD_PENALTY_AREA_RADIUS);
//    Vector2D dir(world->mainBall()->Position() - SSL::Position::ourGoalCenter());
//    dir.normalize();
//    dir.rotate(displaceAngle);
//    if(!analyzer->isPointInOurSide(Ball_Position)) {
//        dir *= ROBOT_RADIUS + FIELD_PENALTY_AREA_RADIUS * 1.80;
//    }
//    else {
//        dir *= ROBOT_RADIUS + FIELD_PENALTY_AREA_RADIUS * 1.30;
//    }
//    Vector3D target(dir + SSL::Position::ourGoalCenter(), dir.arctan());
//    return target;


//    Vector2D point_to_defend = SSL::Position::ourGoalCenter();

//    Vector2D risky_object_pos;
//    Vector2D ball_kick_aim = analyzer->ballIntersectionWithOurGoalLine();
//    if(fabs(analyzer->ballIntersectionWithOurGoalLine().Y()) < FIELD_GOAL_WIDTH_2 * 1.5) {
//        ball_kick_aim.setY( bound(ball_kick_aim.Y(), -FIELD_GOAL_WIDTH_2, FIELD_GOAL_WIDTH_2) );
//        point_to_defend = ball_kick_aim;
//    }
//    if(Ball_Speed.lenght() < 2000) {
//        risky_object_pos = Ball_Position;
//    } else {
//        SSLRobot* nearest_ = analyzer->nearestToBall(game->opponentTeam()->getInFieldRobots());
//        if(nearest_ != NULL) {
//            risky_object_pos = nearest_->Position().to2D();
//        }
//    }
//    Vector2D risk_vec = (risky_object_pos - ball_kick_aim).normalized();
//    if(m_defenderIndex == 1)
//        risk_vec.rotate(-0.05);
//    else
//        risk_vec.rotate(0.05);
//    Vector2D target = point_to_defend + risk_vec * (FIELD_PENALTY_AREA_RADIUS + ROBOT_RADIUS*2);
//    float orien = SSL::Position::seePointOrientation(target, risky_object_pos);

//    return Vector3D(target, orien);
}

int Defender::getDefenderIndex() const
{
    return m_defenderIndex;
}

void Defender::setDefenderIndex(int ind)
{
    m_defenderIndex = ind;
}

int Defender::getDefenderCount() const
{
    return m_defenderCount;
}

void Defender::setDefenderCount(int ind)
{
    m_defenderCount = ind;
}

void Defender::run()
{
    if(!analyzer->isPointWithinOurPenaltyArea(Ball_Position) && analyzer->isPointInOurSide(Ball_Position)) {
        if(analyzer->canKick(this->m_agent->robot)) {
            m_agent->skill->goAndKick(Ball_Position, SSL::Position::opponenetGoalFocalPointTop());
        }
    }
    else {
        m_agent->skill->goToPointWithPlanner(expectedPosition(),
                                             SSLSkill::defaultTolerance,
                                             true,
                                             0,
                                             0,
                                             SSLSkill::eFastMove);
    }


//    float x = (float)(m_defenderCount + 1)/2.0;
//    float displaceAngle = (m_defenderIndex - x) * (2 *ROBOT_RADIUS /FIELD_PENALTY_AREA_RADIUS);
//    Vector2D dir(Ball_Position - SSL::Position::ourGoalCenter());
//    dir.rotate(displaceAngle);
//    float radius;
//    float arc_len_ = fabs(fabs(dir.arctan()) - M_PI_2);
//    if( dir.lenght() > FIELD_LENGTH_2 ) {
//        radius = FIELD_PENALTY_AREA_RADIUS * 1.4;
//    }
//    else if(arc_len_ > atan(2.0)) {
//        radius = FIELD_PENALTY_AREA_RADIUS * 1.07 + ROBOT_RADIUS;
//    }
//    else
//        radius = FIELD_PENALTY_AREA_RADIUS * 1.1 + ROBOT_RADIUS + ( atan(2.0) - arc_len_ ) * 500;
//    dir.normalize();
//    dir *= radius;
//    Vector3D target(dir + SSL::Position::ourGoalCenter(), dir.arctan());
//    target.setX(bound(target.X(), -FIELD_LENGTH_2 + ROBOT_RADIUS, FIELD_LENGTH_2 - ROBOT_RADIUS));
//    m_agent->skill->goToPointWithPlanner(target, SSLSkill::defaultTolerance, true, 0, 0, SSLSkill::eFastMove);

}
