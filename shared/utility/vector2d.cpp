#include "vector2d.h"
#include "vector3d.h"
#include "linesegment.h"
#include "generalmath.h"
#include <cmath>
#include <ostream>

#ifdef _USE_QT_
#include <QVector3D>
#include <QVector2D>
#include <QPointF>
#endif

#ifdef _USE_BOX2D_
#include <Box2D/Common/b2Math.h>
#endif

Vector2D::Vector2D()
{
    _x = _y = 0;
}

Vector2D::Vector2D(const Vector2D &vector)
{
    _x = vector._x; _y = vector._y;
}

Vector2D::Vector2D(float nx, float ny)
{
    _x = nx;    _y = ny;
}

Vector2D Vector2D::operator=(const Vector2D &vector)
{
    _x = vector._x; _y = vector._y;
    return *this;
}

bool Vector2D::operator==(const Vector2D &vector) const
{
    return _x == vector._x && _y == vector._y;
}

bool Vector2D::operator!=(const Vector2D &vector) const
{
    return _x != vector._x || _y != vector._y;
}

void Vector2D::setZero()
{
    _x = _y = 0.0;
}

void Vector2D::rotate(float radian_rot)
{
    float new_x, new_y;
    new_x = _x * cos(radian_rot) - _y * sin(radian_rot);
    new_y = _x * sin(radian_rot) + _y * cos(radian_rot);
    _x = new_x;
    _y = new_y;
}

float Vector2D::lenght() const
{
    double v2 = _x * _x + _y * _y;
    return sqrt(v2);
}

float Vector2D::arctan() const
{
    return atan2(_y, _x);
}

float Vector2D::distToLine(const LineSegment &ls) const
{
    float line_slope = atan2(ls.dy(), ls.dx());
    float a1 = tan(line_slope);
    float a2 = tan(line_slope + M_PI_2);

    float b1 = ls.y1()   - a1 * ls.x1();
    float b2 = this->Y() - a2 * this->X();

    float intersect_x = (b2-b1)/(a1-a2);
    float intersect_y = a1 * intersect_x + b1;

    return distance(*this, Vector2D(intersect_x, intersect_y));
    // farzad
    /*
     *float SSLAnalyzer::distance_point_line(const Vector2D &a, const Vector2D &b, const Vector2D &c) const

    // a,b,c are points, |ch| is returned
    float distancePointPoint = hypot(a.X() - b.X(), a.Y() - b.Y());
    if (distancePointPoint < 1e-9)
        return INFINITY;
    Vector2D ac = (c-a);
    Vector2D ab = (b-a);
    float cross = ac.X()*ab.Y() + ac.Y()*ab.X();
    return fabs(cross)/ distancePointPoint;

     */

}

Vector2D Vector2D::operator -() const
{
    return Vector2D(-_x, -_y);
}

Vector2D Vector2D::operator +(const Vector2D &vector) const
{
    return Vector2D( _x + vector._x, _y + vector._y);
}

Vector2D Vector2D::operator -(const Vector2D &vector) const
{
    return Vector2D( _x - vector._x, _y - vector._y);
}

Vector2D Vector2D::operator *(float s)
{
    return Vector2D( _x*s, _y*s);
}

Vector2D Vector2D::operator /(float s)
{
    float oneOverS = 1.0f / s;
    return Vector2D( _x*oneOverS, _y*oneOverS);
}

Vector2D &Vector2D::operator +=(const Vector2D &vector)
{
    _x += vector._x; _y += vector._y;
    return *this;
}

Vector2D &Vector2D::operator -=(const Vector2D &vector)
{
    _x -= vector._x; _y -= vector._y;
    return *this;
}

Vector2D &Vector2D::operator *=(float s)
{
    _x *= s; _y *= s;
    return *this;
}

Vector2D &Vector2D::operator /=(float s)
{
    float oneOverS = 1.0f / s;
    _x *= oneOverS; _y *= oneOverS;
    return *this;
}

bool Vector2D::operator <(const Vector2D &vector) const
{
    return (this->X()<vector.X() || (!(this->X() > vector.X()) && (this->Y() < vector.Y())));
}

void Vector2D::normalize()
{
    float magSqrd = _x*_x + _y*_y;
    if(magSqrd > 0.0f){
        float oneOverMag = 1.0 / sqrt(magSqrd);
        _x *= oneOverMag;
        _y *= oneOverMag;
    }
    else
        this->set(sqrt(2)/2, sqrt(2)/2);
}

Vector2D Vector2D::normalized() const
{
    Vector2D temp(this->_x, this->_y);
    float magSqrd = _x*_x + _y*_y;
    if(magSqrd > 0.0f)
    {
        float oneOverMag = 1.0 / sqrt(magSqrd);
        temp._x *= oneOverMag;
        temp._y *= oneOverMag;
    }
    else
        temp.set(sqrt(2)/2, sqrt(2)/2);

    return temp;
}

bool Vector2D::isInf() const
{
    if(_x == INFINITY || _y == INFINITY)
        return true;
    return false;
}

float Vector2D::operator *(const Vector2D &vector)
{
    return (_x * vector._x) + (_y * vector._y);
}

Vector3D Vector2D::to3D()
{
    Vector3D v3d(this->_x, this->_y, 0.0f);
    return v3d;
}

#ifdef _USE_BOX2D_
Vector2D::Vector2D(b2Vec2 vec)
{
    _x = vec.x;
    _y = vec.y;
}

b2Vec3 Vector2D::toB2vec3()
{
    return b2Vec3(this->_x, this->_y, 0);
}

b2Vec2 Vector2D::toB2vec2()
{
    return b2Vec2(this->_x, this->_y);
}
#endif

#ifdef _USE_QT_
Vector2D::Vector2D(QVector2D &qvec)
{
    _x = qvec.x();
    _y = qvec.y();
}

Vector2D::Vector2D(QPointF qpnt)
{
    _x = qpnt.x();
    _y = qpnt.y();
}

QVector3D Vector2D::toQvec3D()
{
    return QVector3D(_x, _y, 0);
}

QVector2D Vector2D::toQvec2D()
{
    return QVector2D(_x, _y);
}

QPointF Vector2D::toQpoint()
{
    return QPointF(_x, _y);
}

#endif

void Vector2D::print(std::ostream &stream)
{
    stream << "X: " << _x << ", Y:" << _y << std::endl;
}

float Vector2D::vectorMag(const Vector2D &vector)
{
    return sqrt(vector._x * vector._x + vector._y * vector._y);
}

float Vector2D::distance(const Vector2D &a, const Vector2D &b)
{
    float dx = a._x - b._x;
    float dy = a._y - b._y;
    return sqrt(dx * dx + dy * dy);
}

Vector2D Vector2D::unitVector(float direction_rad)
{
    Vector2D tmp(1, 0);
    tmp.rotate(direction_rad);
    return tmp;
}

float Vector2D::dot(const Vector2D &a, const Vector2D &b)
{
    return a._x*b._x + a._y*b._y;
}

float Vector2D::angleBetween(const Vector2D &a, const Vector2D &b)
{
    float mulOfLengths = a.lenght() * b.lenght();
    if (mulOfLengths == 0.0)
        return 0.0;
    float cos_theta = Vector2D::dot(a, b) / mulOfLengths;
    return acos(cos_theta);
}

void Vector2D::set(float x_, float y_)
{
    this->_x = x_;
    this->_y = y_;
}

void Vector2D::setX(float x_)
{
    this->_x = x_;
}

void Vector2D::setY(float y_)
{
    this->_y = y_;
}

float Vector2D::X() const
{
    return this->_x;
}

float Vector2D::Y() const
{
    return this->_y;
}

std::ostream& operator<< (std::ostream &out, Vector2D &p)
{
    p.print(out);
}
