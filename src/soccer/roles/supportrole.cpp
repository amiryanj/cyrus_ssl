#include "supportrole.h"

SupportRole::SupportRole(SSLAgent *agent)
{
    this->m_agent = agent;
    this->m_type = SSLRole::Support;
}

void SupportRole::run()
{

//    if(SSLAnalyzer::getInstance()->canKick(getRobot())){
//        SSLSkill::getInstance()->goToPointAndKickForGoal(getRobot());
//    }else if(SSLAnalyzer::getInstance()->canStealBall(getRobot())){
//        SSLSkill::getInstance()->goToPointAndKickForGoal(getRobot());
//    }else if(SSLAnalyzer::havingBallColor() == SSLGame::getInstance()->ourColor()){
//        Vector2D target (0, SSLGame::getInstance()->enemySide() * (double)FIELD_LENGTH /4.0);
//        Vector2D theirGoalPos = SSLSocerMath::getGoalPosition(SSLGame::getInstance()->enemySide());

//        SSLSkill::getInstance()->goToPoint(getRobot(),
//                                           target,
//                                           SSLSocerMath::getFacingToPoint(target, theirGoalPos));
//    }else{
//        SSLSkill::getInstance()->goToPointAndKickForGoal(getRobot());
//    }


}
