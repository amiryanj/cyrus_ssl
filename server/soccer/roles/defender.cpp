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
    float x = (float)(m_defenderCount + 1)/2.0;
    float displaceAngle = (m_defenderIndex - x) * (1.6 *ROBOT_RADIUS /FIELD_PENALTY_AREA_RADIUS);
    Vector2D dir(world->mainBall()->Position() - SSL::Position::ourGoalCenter());
    dir.normalize();
    dir.rotate(displaceAngle);
    dir *= FIELD_PENALTY_AREA_RADIUS * 1.33;
    Vector3D target(dir + SSL::Position::ourGoalCenter(), dir.arctan());
    return target;
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
    float x = (float)(m_defenderCount + 1)/2.0;
    float displaceAngle = (m_defenderIndex - x) * (2 *ROBOT_RADIUS /FIELD_PENALTY_AREA_RADIUS);
    Vector2D dir(Ball_Position - SSL::Position::ourGoalCenter());
    dir.rotate(displaceAngle);
    float radius;
    float arc_len_ = fabs(fabs(dir.arctan()) - M_PI_2);
    if( dir.lenght() > FIELD_LENGTH_2 ) {
        radius = FIELD_PENALTY_AREA_RADIUS * 1.4;
    }
    else if(arc_len_ > atan(2.0)) {
        radius = FIELD_PENALTY_AREA_RADIUS * 1.07 + ROBOT_RADIUS;
    }
    else
        radius = FIELD_PENALTY_AREA_RADIUS * 1.1 + ROBOT_RADIUS + ( atan(2.0) - arc_len_ ) * 500;
    dir.normalize();
    dir *= radius;
    Vector3D target(dir + SSL::Position::ourGoalCenter(), dir.arctan());
    target.setX(bound(target.X(), -FIELD_LENGTH_2 + ROBOT_RADIUS, FIELD_LENGTH_2 - ROBOT_RADIUS));
    m_agent->skill->goToPointWithPlanner(target, SSLSkill::defaultTolerance, true, 0, 0, SSLSkill::eFastMove);

}
