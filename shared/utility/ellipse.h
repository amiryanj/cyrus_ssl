#ifndef _ELLIPSE_H
#define _ELLIPSE_H

#include "shape.h"
#include "vector2d.h"

class Ellipse : public Shape
{
public:
    Ellipse();
    Ellipse(Vector2D cnt_1, Vector2D cnt_2, double len_);

    double m_diameter; // find the right name for this element (I'm sure it's wrong)
    Vector2D m_center1, m_center2;

    Vector2D mainCenter() const;
    double orientation() const;
    double shortRadius() const;
    double longRadius() const;
    double centersDistance() const;

    bool isValid();

};

#endif // _ELLIPSE_H
