#ifndef _LINESEGMENT_H
#define _LINESEGMENT_H

#include "vector2d.h"

class LineSegment
{
public:    
    inline LineSegment();
    inline LineSegment(const Vector2D &pt1, const Vector2D &pt2);
    inline LineSegment(float x1, float y1, float x2, float y2);

    inline bool isNull() const;

    inline Vector2D p1() const;
    inline Vector2D p2() const;

    inline float x1() const;
    inline float y1() const;

    inline float x2() const;
    inline float y2() const;

    inline float dx() const;
    inline float dy() const;

    inline void translate(const Vector2D &p);
    inline void translate(float dx, float dy);

    inline LineSegment translated(const Vector2D &p) const;
    inline LineSegment translated(float dx, float dy) const;

    inline void setP1(const Vector2D &p1);
    inline void setP2(const Vector2D &p2);
    inline void setPoints(const Vector2D &p1, const Vector2D &p2);
    inline void setLine(float x1, float y1, float x2, float y2);

    static Vector2D intersection(const LineSegment l1, const LineSegment& l2);
    float slope() const;

    inline bool operator==(const LineSegment &d) const;
    inline bool operator!=(const LineSegment &d) const { return !(*this == d); }

private:
    Vector2D pt1, pt2;
};


/*******************************************************************************
 * class LineSegment inline members
 *******************************************************************************/

inline LineSegment::LineSegment() { }

inline LineSegment::LineSegment(const Vector2D &pt1_, const Vector2D &pt2_) : pt1(pt1_), pt2(pt2_) { }

inline LineSegment::LineSegment(float x1pos, float y1pos, float x2pos, float y2pos) : pt1(Vector2D(x1pos, y1pos)), pt2(Vector2D(x2pos, y2pos)) { }

inline bool LineSegment::isNull() const
{
    return (pt1 == pt2);
}

inline float LineSegment::x1() const
{
    return pt1.X();
}

inline float LineSegment::y1() const
{
    return pt1.Y();
}

inline float LineSegment::x2() const
{
    return pt2.X();
}

inline float LineSegment::y2() const
{
    return pt2.Y();
}

inline Vector2D LineSegment::p1() const
{
    return pt1;
}

inline Vector2D LineSegment::p2() const
{
    return pt2;
}

inline float LineSegment::dx() const
{
    return pt2.X() - pt1.X();
}

inline float LineSegment::dy() const
{
    return pt2.Y() - pt1.Y();
}

inline void LineSegment::translate(const Vector2D &point)
{
    pt1 += point;
    pt2 += point;
}

inline void LineSegment::translate(float adx, float ady)
{
    this->translate(Vector2D(adx, ady));
}

inline LineSegment LineSegment::translated(const Vector2D &p) const
{
    return LineSegment(pt1 + p, pt2 + p);
}

inline LineSegment LineSegment::translated(float adx, float ady) const
{
    return translated(Vector2D(adx, ady));
}

inline void LineSegment::setP1(const Vector2D &aP1)
{
    pt1 = aP1;
}

inline void LineSegment::setP2(const Vector2D &aP2)
{
    pt2 = aP2;
}

inline void LineSegment::setPoints(const Vector2D &aP1, const Vector2D &aP2)
{
    pt1 = aP1;
    pt2 = aP2;
}

inline void LineSegment::setLine(float aX1, float aY1, float aX2, float aY2)
{
    pt1 = Vector2D(aX1, aY1);
    pt2 = Vector2D(aX2, aY2);
}

inline bool LineSegment::operator==(const LineSegment &d) const
{
    return pt1 == d.pt1 && pt2 == d.pt2;
}

#endif // _LINESEGMENT_H
