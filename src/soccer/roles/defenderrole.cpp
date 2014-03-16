#include "defenderrole.h"

DefenderRole::DefenderRole(SSLAgent *agent)
{
    this->m_agent = agent;
    this->m_type = SSLRole::Defender;
}

int DefenderRole::getDefenderIndex() const
{
    return m_defenderIndex;
}

void DefenderRole::setDefenderIndex(int ind)
{
    m_defenderIndex = ind;
}

int DefenderRole::getDefenderCount() const
{
    return m_defenderCount;
}

void DefenderRole::setDefenderCount(int ind)
{
    m_defenderCount = ind;
}

void DefenderRole::run(){

//    Vector2D target;
//    float facing = 0;

//    switch (getDefenderCount()) {
//    case 1:
//        if(SSLAnalyzer::getInstance()->getTimeToBall(*getRobot()) <= DefenderRole::SMALLEST_TIME_TO_SHOOT){
//            //If ball is too close, go for ball and shoot!

////            target.setX(SSLWorldModel::getInstance()->ball->Position().X());
////            target.setY(SSLWorldModel::getInstance()->ball->Position().Y());

////            facing = SSLSocerMath::getFacingToPoint(getRobot()->Position().to2D(), Vector2D((double)0, SSLGame::getInstance()->enemySide() * FIELD_LENGTH/ (double)2));

//            SSLSkill::getInstance()->goToPointKickForBlock(getRobot());
//        }else{
//            //Go between ball and Goal

////            Vector2D ourGoal(0, SSLGame::getInstance()->ourSide() * FIELD_LENGTH/ (double)2);

////            target.setX((SSLWorldModel::getInstance()->ball->Position().X() + ourGoal.X()) / (double)2);
////            target.setY((SSLWorldModel::getInstance()->ball->Position().Y() + ourGoal.Y()) / (double)2);

////            facing = SSLSocerMath::getFacingToPoint(getRobot()->Position().to2D(), Vector2D((double)0, SSLGame::getInstance()->enemySide() * FIELD_LENGTH/ (double)2));

//            Vector2D offenserPos = SSLWorldModel::getInstance()->ball->Position();
//            Vector2D ourGoalPos = SSLSocerMath::getGoalPosition(SSLGame::getInstance()->ourSide());
//            Vector2D target = SSLSocerMath::getBlockPosition(offenserPos,
//                                                             ourGoalPos,
//                                                             getDefenderCount(),
//                                                             getDefenderIndex(),
//                                                             50.0);

//            SSLSkill::goToPoint(getRobot(),
//                                target,
//                                SSLSocerMath::getFacingToPoint(target, offenserPos));


//        }

//        break;
//    case 2:

//        if(SSLAnalyzer::getInstance()->getTimeToBall(*getRobot()) <= DefenderRole::SMALLEST_TIME_TO_SHOOT){
//            //If ball is too close, go for ball and shoot!

//            SSLSkill::getInstance()->goToPointKickForBlock(getRobot());
//        }else{
//            //Go between ball and Goal

////            Vector2D ourGoal(0, SSLGame::getInstance()->ourSide() * FIELD_LENGTH/ (double)2);

////            target.setX((SSLWorldModel::getInstance()->ball->Position().X() + ourGoal.X()) / (double)2);
////            target.setY((SSLWorldModel::getInstance()->ball->Position().Y() + ourGoal.Y()) / (double)2);

////            facing = SSLSocerMath::getFacingToPoint(getRobot()->Position().to2D(), Vector2D((double)0, SSLGame::getInstance()->enemySide() * FIELD_LENGTH/ (double)2));

//            Vector2D offenserPos = SSLWorldModel::getInstance()->ball->Position();
//            Vector2D ourGoalPos = SSLSocerMath::getGoalPosition(SSLGame::getInstance()->ourSide());
//            Vector2D target = SSLSocerMath::getBlockPosition(offenserPos,
//                                                             ourGoalPos,
//                                                             getDefenderCount(),
//                                                             getDefenderIndex(),
//                                                             50.0);

//            SSLSkill::goToPoint(getRobot(),
//                                target,
//                                SSLSocerMath::getFacingToPoint(target, offenserPos));

//        }

//        break;
//    case 3:

//        break;
//    default:
//        break;
//    }


}
