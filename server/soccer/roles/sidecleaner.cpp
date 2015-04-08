#include "sidecleaner.h"
#include "../../../common/math/linesegment.h"
#include "../../definition/SSLTeam.h"
#include "../../definition/SSLRobot.h"
#include "../sslskill.h"
#include "../sslagent.h"

SideCleaner::SideCleaner(CleanSide _side)
{
    this->m_type = SSLRole::e_SideCleaner;
    this->m_side = _side;

    m_hardness = 2;
}

void SideCleaner::run()
{
    Vector2D point_to_defend = this->expectedPosition().to2D();

    Vector2D risky_opponent_pos;
    vector<SSLRobot*> op_robot_set = game->opponentTeam()->getInFieldRobots();
    for(int i=op_robot_set.size()-1; i>=0; i--) {
        SSLRobot* op_robot = ((SSLRobot*)op_robot_set[i]);
        if(fabs(op_robot->Position().X() - SSL::Position::ourGoalCenter().X()) > FIELD_LENGTH_2 * 1.1) {
            op_robot_set.erase(op_robot_set.begin() + i);
            continue;
        }
        if(SSL::sgn(op_robot->Position().Y()) != SSL::sgn(point_to_defend.Y()))
            op_robot_set.erase(op_robot_set.begin() + i);
    }
    SSLRobot* op_risky_robot_ = analyzer->nearestToPoint(op_robot_set, point_to_defend, 0);
    if(op_risky_robot_ != NULL) {
        risky_opponent_pos = op_risky_robot_->Position().to2D();
    }
    else {
        risky_opponent_pos = Vector2D(0.0, 0.0);
    }

    Vector2D risk_vec = risky_opponent_pos - point_to_defend;
    risk_vec.normalize();

    Vector2D target = point_to_defend + risk_vec * (FIELD_PENALTY_AREA_RADIUS + ROBOT_RADIUS*3);
    float orien = SSL::Position::seePointOrientation(target, risky_opponent_pos);

    m_agent->skill->goToPointWithPlanner(Vector3D(target, orien),
                                         SSLSkill::defaultTolerance,
                                         true,
                                         0,
                                         0,
                                         SSLSkill::eFastMove);
}

Vector3D SideCleaner::expectedPosition()
{
    if( m_side == eCleanTopField) {
        return SSL::Position::ourGoalFocalPointTop().to3D();
    }
    else {
        return SSL::Position::ourGoalFocalPointDown().to3D();
    }
}
