#include "blockrole.h"

BlockRole::BlockRole(SSLAgent *agent)
{
    this->m_agent = agent;
    this->m_type = SSLRole::Block;
}

SSLRobot *BlockRole::getBlockedRobot() const
{
    return m_blockedRobot;
}

void BlockRole::setBlockedRobot(SSLRobot *value)
{
    m_blockedRobot = value;
}

void BlockRole::run()
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
