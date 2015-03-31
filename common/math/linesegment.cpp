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

Vector2D LineSegment::intersection(const LineSegment l1, const LineSegment &l2)
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


//    // line equation : ax + by + c = 0
//    float a1 = l1.y1() - l1.y2();
//    float b1 = l1.x2() - l1.x1();
//    float c1 = (l1.x1() - l1.x2()) * l1.y1() + (l1.y2() - l1.y1()) * l1.x1();

//    a1 /= b1;
//    c1 /= b1;
//    b1 = 1.0;

//    float a2 = l2.y1() - l2.y2();
//    float b2 = l2.x2() - l2.x1();
//    float c2 = (l2.x1() - l2.x2()) * l2.y1() + (l2.y2() - l2.y1()) * l2.x1();

//    a2 /= b2;
//    c2 /= b2;
//    b2 = 1.0;



//    float intercept_x = (b2-b1) / (m1-m2);
//    float intercept_y = m1* intercept_x + b1;

}

float LineSegment::slope() const
{
    return tan(atan2( this->dy(), this->dx() ));
}

