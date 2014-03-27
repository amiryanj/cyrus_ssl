#include "wallstander.h"

WallStander::WallStander(float wallRadius, short index, short count)
{
    m_type = SSLRole::e_WallStander;

    m_wallRadius = wallRadius;
    m_standerIndex = index;
    m_standerCount = count;

    m_hardness = 1;
}

void WallStander::run()
{

}

Vector2D WallStander::expectedPosition()
{

}
