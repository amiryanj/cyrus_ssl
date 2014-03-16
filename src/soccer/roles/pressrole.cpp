#include "pressrole.h"

PressRole::PressRole(SSLAgent *agent)
{
    this->m_agent = agent;
    this->m_type = SSLRole::Press;
}

void PressRole::setBlockingRobot(SSLRobot *value)
{
    m_blockingRobot = value;
}

SSLRobot *PressRole::getBlockingRobot() const
{
    return m_blockingRobot;
}

void PressRole::run()
{
//    Vector2D target;
//    float facing;

//    if(SSLAnalyzer::getInstance()->getTimeToBall(*getRobot()) <= PressRole::SMALLEST_TIME_TO_SHOOT){
//        SSLSkill::getInstance()->goToPointAndKickForGoal(getRobot());
//    }else{
//        Vector2D target;
//        float facing;


//        target.setX((SSLWorldModel::getInstance()->ball->Position().X() + getBlockingRobot()->Position().X())/(double)2);
//        target.setY((SSLWorldModel::getInstance()->ball->Position().Y() + getBlockingRobot()->Position().Y())/(double)2);

//        facing = SSLSocerMath::getFacingToPoint(target, getRobot()->Position().to2D());

//        SSLSkill::getInstance()->goToPoint(getRobot(), target, facing);
//    }

}
