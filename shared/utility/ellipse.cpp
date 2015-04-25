#include "ellipse.h"
#include <cmath>

Ellipse::Ellipse()
{
    m_diameter = -1;
}

Ellipse::Ellipse(Vector2D cnt_1, Vector2D cnt_2, double len_)
{
    m_center1 = cnt_1;
    m_center2 = cnt_2;
    m_diameter = len_;
}

Vector2D Ellipse::mainCenter() const
{
    return (m_center1 + m_center2)/2.0;
}

double Ellipse::orientation() const
{
    return (m_center2 - m_center1).arctan();
}

double Ellipse::shortRadius() const
{
    return sqrt((m_diameter/2.0) * (m_diameter/2.0) -
                (centersDistance()/2.0) * (centersDistance()/2.0));
}

double Ellipse::longRadius() const
{
    return m_diameter/2.0;
}

double Ellipse::centersDistance() const
{
    return (m_center2 - m_center1).lenght();
}

bool Ellipse::isValid()
{
    return (m_diameter >= 0);
}
