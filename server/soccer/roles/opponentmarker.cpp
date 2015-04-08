#include "opponentmarker.h"
#include "../sslagent.h"
#include "../sslskill.h"
#include "../../definition/SSLRobot.h"

OpponentMarker::OpponentMarker(int index_)
{
    this->m_type = SSLRole::e_OpponentMarker;
    m_hardness = 2; // may be 1

    this->m_index = index_;
}

void OpponentMarker::run()
{
    Vector3D target = expectedPosition();
    m_agent->skill->goToPointWithPlanner(target, SSLSkill::defaultTolerance,
                                         true, 0, 0, SSLSkill::eFastMove);
}

Vector3D OpponentMarker::expectedPosition()
{
    Vector3D target = SSL::Position::wallStandFrontBall(2, Ball_Position);

    if(world->m_refereeState == SSLReferee::Stop) {
        target = SSL::Position::wallStandFrontBall(-1, Ball_Position);
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
                target = (near_to_goal->Position().to2D() +
                  (SSL::Position::ourGoalCenter() - near_to_goal->Position().to2D()).normalized() * 2.5 * ROBOT_RADIUS).to3D();
                target.setTeta(SSL::Position::seePointOrientation(target.to2D(),
                                                                  near_to_goal->Position().to2D()));

                if(analyzer->isPointInOurSide(target.to2D())) {
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
