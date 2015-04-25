#include "linesegment.h"
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/linestring.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/segment.hpp>
#include <cmath>
#include <vector>
#include <stdio.h>

using namespace boost::geometry::model;
using namespace std;

typedef boost::geometry::model::point<double, 2, boost::geometry::cs::cartesian> Point;
typedef boost::geometry::model::segment<Point> Segment;

Vector2D LineSegment::intersection(const LineSegment &l1, const LineSegment &l2)
{
    Segment line_seg1(Point(l1.x1(), l1.y1(), 0.0),
                      Point(l1.x2(), l1.y2(), 0.0));

    Segment line_seg2(Point(l2.x1(), l2.y1(), 0.0),
                      Point(l2.x2(), l2.y2(), 0.0));

    vector<Point> output;
    boost::geometry::intersection(line_seg1, line_seg2, output);

    if( !output.empty() ) {
        Point p = output.front();
        return Vector2D(p.get<0>(), p.get<1>());
    }
    return Vector2D(INFINITY, INFINITY);
}

double LineSegment::slope() const
{
    return tan( atan2( this->dy(), this->dx() ) );
}

LineSegment LineSegment::prependicularLine(const Vector2D p) const
{
    Vector2D prependicular_vector = Vector2D::unitVector(atan(this->slope()) + M_PI_2l) * 1000000;
    LineSegment prependicular_line(p - prependicular_vector , p + prependicular_vector);
    return prependicular_line;
}

Vector2D LineSegment::nearestPointFrom(const Vector2D &p) const
{
    LineSegment prependicular_line = this->prependicularLine(p);
    Vector2D intercept_point = LineSegment::intersection(*this, prependicular_line);
    if( intercept_point.X() < INFINITY )  {
        return intercept_point;
    }
    else if( Vector2D::distance(p, this->p1()) < Vector2D::distance(p, this->p2()) ) {
        return this->p1();
    }
    else {
        return this->p2();
    }
}

