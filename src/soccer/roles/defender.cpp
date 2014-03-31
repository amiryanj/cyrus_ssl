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

////            Vector2D ourGoal(SSLGame::getInstance()->ourSide() * FIELD_LENGTH/ (double)2, 0);

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
