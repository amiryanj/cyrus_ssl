#include "blocker.h"

Blocker::Blocker()
{
    this->m_type = SSLRole::e_Blocker;

    m_hardness = 2;
}

SSLRobot *Blocker::getBlockedRobot() const
{
    return m_blockedRobot;
}

void Blocker::setBlockedRobot(SSLRobot *value)
{
    m_blockedRobot = value;
}

void Blocker::run()
{
    Vector3D target = expectedPosition();
    Vector3D tolerance(100, 100, M_PI);
    SSLSkill::goToPointWithPlanner(m_agent, target, tolerance, true);
}

Vector3D Blocker::expectedPosition()
{
    SSL::Color op_color = game->opponentColor();
    Vector2D opponent_pos(0, 0);
    SSLRobot* nearToBall = NULL;
    SSLAnalyzer::RobotIntersectTime temp_intersect_ = analyzer->nearestRobotToBall(op_color);
    if(temp_intersect_.isValid())
        nearToBall = temp_intersect_.m_robot;
    vector<SSLRobot* > others = world->getTeam(op_color)->inFieldsExcept(nearToBall);
    temp_intersect_ = analyzer->nearestRobotToPoint(others, SSLSkill::ourGoalCenter(), 0);
    if(temp_intersect_.isValid()) {
        SSLRobot* nearToOurGoal = temp_intersect_.m_robot;
        if(!analyzer->isPointWithinOurPenaltyArea(nearToOurGoal->Position().to2D())) {
            opponent_pos = nearToOurGoal->Position().to2D();
            if((opponent_pos - SSLSkill::ourGoalCenter()).lenght() < FIELD_LENGTH / 2) {

            }
        }
    }
    Vector2D diff = opponent_pos - SSLSkill::ourGoalCenter();
    diff.normalize();
    Vector2D target = SSLSkill::ourGoalCenter() + diff * FIELD_PENALTY_AREA_RADIUS * 1.5;
    return target.to3D();
}

