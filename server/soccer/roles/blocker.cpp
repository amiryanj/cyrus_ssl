#include "blocker.h"
#include "../sslagent.h"
#include "../sslskill.h"
#include "../../definition/SSLRobot.h"

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
    m_agent->skill->goToPointWithPlanner(target, tolerance, true, 0, ROBOT_RADIUS, SSLSkill::eFastMove);
}

Vector3D Blocker::expectedPosition()
{
    Vector3D target = SSL::Position::wallStandFrontBall(-1, world->mainBall()->Position());

    if(world->m_refereeState == SSLReferee::Stop) {
        target = SSL::Position::wallStandFrontBall(-1, world->mainBall()->Position());
    }

    else if(analyzer->isOpponentPenaltyPosition() || analyzer->isOpponentPenaltyKick()) {
        target = SSL::Position::ourMidfieldDownPosition();
    }

    else {

        SSLRobot* near_to_ball = analyzer->nearestToBall(game->opponentTeam()->getInFieldRobots(), 0);
        if(near_to_ball != NULL) {
            SSLRobot* near_to_goal = analyzer->nearestToPoint(game->opponentTeam()->getInFieldRobotsExcept(near_to_ball),
                                                              SSL::Position::ourGoalCenter(), m_index-1 );
            if(near_to_goal != NULL) {
                float near_to_goal_dist = (near_to_goal->Position().to2D() - SSL::Position::ourGoalCenter()).lenght();
                near_to_goal_dist = fabs(near_to_goal_dist - FIELD_PENALTY_AREA_RADIUS * 1.5);
                target = SSL::Position::DefenseStylePosition(near_to_goal->Position().to2D(),
                                                             SSL::Position::ourGoalCenter(),
                                                             near_to_goal_dist/2);
                if(!analyzer->isRobotWithinOurPenaltyArea(target) && analyzer->isPointInOurSide(target.to2D())) {
                   return target;
                }
            }
        }
    }

    if(m_index == 1) {
        target = SSL::Position::ourMidfieldDownPosition();
    }
    else {
        target = SSL::Position::ourMidfieldUpPosition();
    }

    return target;
}

