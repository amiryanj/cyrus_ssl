#include "waitpass.h"

WaitPass::WaitPass()
{
    this->m_type = SSLRole::e_WaitPass;    

    m_hardness = 2;
}

Vector3D WaitPass::getBestPosition() const
{
    return m_bestPosition;
}

void WaitPass::setBestPosition(const Vector3D &value)
{
    m_bestPosition = value;
}

Vector2D WaitPass::expectedPosition()
{
}

void WaitPass::run()
{

}
