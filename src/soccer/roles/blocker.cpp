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
//    if(SSLAnalyzer::getInstance()->canKick(getRobot())){
//        SSLSkill::getInstance()->goToPointAndKickForGoal(getRobot());
//    }else if(SSLAnalyzer::getInstance()->canStealBall(getRobot())){
//        SSLSkill::getInstance()->goToPointAndKickForGoal(getRobot());
//    }else if(SSLAnalyzer::getInstance()->haveBall(getBlockedRobot())){
//        Vector2D ballPos = SSLWorldModel::getInstance()->ball->Position();
//        Vector2D ourGoalPos = SSLSocerMath::getGoalPosition(SSLGame::getInstance()->ourSide());

//        SSLSkill::getInstance()->goToPoint(getRobot(),
//                            Vector2D((ballPos.X() + ourGoalPos.X()) / 2, (ballPos.Y() + ourGoalPos.Y()) / 2),
//                            SSLSocerMath::getFacingToPoint(getRobot()->Position().to2D(), ballPos));
//    }else{
//        Vector2D blockingRobotPos = getBlockedRobot()->Position().to2D();
//        Vector2D ourGoalPos = SSLSocerMath::getGoalPosition(SSLGame::getInstance()->ourSide());

//        SSLSkill::getInstance()->goToPoint(getRobot(),
//                            Vector2D((blockingRobotPos.X() + ourGoalPos.X()) / 2, (blockingRobotPos.Y() + ourGoalPos.Y()) / 2),
//                            SSLSocerMath::getFacingToPoint(getRobot()->Position().to2D(), ourGoalPos));
//    }

}

Vector2D Blocker::expectedPosition()
{
    SSL::Color op_color = game->opponentColor();

    SSLRobot* nearBall = NULL;
    SSLAnalyzer::RobotIntersectTime temp_intersect_ = analyzer->nearestRobotToBall(op_color);
    if(temp_intersect_.isValid())
        nearBall = temp_intersect_.m_robot;
    vector<SSLRobot* > others = world->getTeam(op_color)->inFieldsExcept(nearBall);
    temp_intersect_ = analyzer->nearestRobotToPoint(others, SSLSkill::ourGoalCenter(), 0);
    if(temp_intersect_.isValid()) {
        SSLRobot* nearOurGoal = temp_intersect_.m_robot;
        Vector2D opponent_pos = nearOurGoal->Position().to2D();
        if(!analyzer->isPointWithinOurPenaltyArea(opponent_pos)) {
            Vector2D diff = opponent_pos - SSLSkill::ourGoalCenter();
            if(diff.lenght() < FIELD_LENGTH / 2){} //
            diff.normalize();
//            Vector2D target =
        }

    }




}
