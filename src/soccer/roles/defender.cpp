#include "defender.h"

Defender::Defender(int ind, int count)
{
    this->m_type = SSLRole::e_Defender;
    m_defenderCount = count;
    m_defenderIndex = ind;

    assert(ind <= count);

    m_hardness = 1;
}

Vector2D Defender::expectedPosition()
{
    float x = (float)(m_defenderCount + 1)/2.0;
    float displaceAngle = (m_defenderIndex - x) * (2 *ROBOT_RADIUS /FIELD_PENALTY_AREA_RADIUS);
    Vector2D dir(world->mainBall()->Position() - SSLSkill::ourGoalCenter());
    dir.normalize();
    dir.rotate(displaceAngle);
    dir *= FIELD_PENALTY_AREA_RADIUS * 1.33;
    Vector3D target(dir + SSLSkill::ourGoalCenter(), dir.arctan());
    return target.to2D();
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
    Vector2D dir(world->mainBall()->Position() - SSLSkill::ourGoalCenter());
    dir.normalize();
    dir.rotate(displaceAngle);
    dir *= FIELD_PENALTY_AREA_RADIUS * 1.3;
    Vector3D target(dir + SSLSkill::ourGoalCenter(), dir.arctan());
    Vector3D tolerance(100, 100, M_PI_4);
    SSLSkill::goToPointWithPlanner(m_agent, target, tolerance, true, 0, 0);

}
