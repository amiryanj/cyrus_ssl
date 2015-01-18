#include "blocker.h"

Blocker::Blocker(int index_)
{
    this->m_type = SSLRole::e_Blocker;
    this->m_index = index_;

    m_hardness = 2;
}

void Blocker::run()
{
    Vector3D target = expectedPosition();
    Vector3D tolerance(100, 100, M_PI);
    SSLSkill::goToPointWithPlanner(m_agent, target, tolerance, true);
}

Vector3D Blocker::expectedPosition()
{
    Vector3D target;

    if(world->m_refereeState == SSLReferee::Stop) {
        target = SSLSkill::wallStandFrontBall(-1);
    }

    else if(analyzer->isOpponentPenaltyPosition() || analyzer->isOpponentPenaltyKick()) {
        target = SSLSkill::ourMidfieldDownPosition();
    }

    else {

        SSLRobot* near_to_ball = analyzer->nearestToBall(game->opponentTeam()->inFields(), m_index - 1);
        if(near_to_ball != NULL) {
            SSLRobot* near_to_goal = analyzer->nearestToPoint(game->opponentTeam()->inFieldsExcept(near_to_ball),
                                                              SSLSkill::ourGoalCenter());
            if(near_to_goal != NULL) {
                float near_to_goal_dist = (near_to_goal->Position().to2D() - SSLSkill::ourGoalCenter()).lenght();
                near_to_goal_dist = fabs(near_to_goal_dist - FIELD_PENALTY_AREA_RADIUS * 1.5);
                target = SSLSkill::DefenseStylePosition(near_to_goal->Position().to2D(), SSLSkill::ourGoalCenter(), near_to_goal_dist/2);
                if(!analyzer->isRobotWithinOurPenaltyArea(target) && analyzer->isPointInOurSide(target.to2D())) {
                   return target;
                }
            }
        }
    }

    if(m_index == 1) {
        target = SSLSkill::ourMidfieldDownPosition();
    }
    else {
        target = SSLSkill::ourMidfieldUpPosition();
    }

    return target;
}

