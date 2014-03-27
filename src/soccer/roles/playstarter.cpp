#include "playstarter.h"

PlayStarter::PlayStarter()
{
    this->m_type = SSLRole::e_PlayStarter;

    m_hardness = 2;
}

Vector3D PlayStarter::getBestPosition() const
{
    return m_bestPosition;
}

void PlayStarter::setBestPosition(const Vector3D &value)
{
    m_bestPosition = value;
}

Vector2D PlayStarter::expectedPosition()
{
    Vector2D pos;
    switch (m_kickType) {
    case e_KickOff:
        pos = SSLSkill::KickStylePosition(Vector2D(0, 0), SSLSkill::opponentGoalCenter()).to2D();
        break;
    case e_Penalty:
        pos = SSLSkill::KickStylePosition(SSLSkill::opponentPenaltyPoint(), SSLSkill::opponentGoalCenter()).to2D();
        break;
    default:
        pos = SSLSkill::KickStylePosition(SSLWorldModel::getInstance()->mainBall()->Position(),
                                                SSLSkill::opponentGoalCenter()).to2D();
        break;
    }
    return pos;
}

void PlayStarter::run()
{

}
