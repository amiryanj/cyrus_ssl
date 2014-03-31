
#include "vector2d.h"
#include "vector3d.h"
#include <math.h>
#include <Box2D/Common/b2Math.h>

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

Vector2D::Vector2D(b2Vec2 vec)
{
    _x = vec.x;  _y = vec.y;
}

Vector2D Vector2D::operator =(const Vector2D &vector)
{
    _x = vector._x; _y = vector._y;
    return *this;
}

bool Vector2D::operator ==(const Vector2D &vector)
{
    return _x == vector._x && _y == vector._y;
}

bool Vector2D::operator !=(const Vector2D &vector)
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

float Vector2D::lenght()
{
    return sqrt(_x*_x + _y*_y);
}

float Vector2D::arctan()
{
    return atan2(_y, _x);
}

Vector2D Vector2D::operator -() const
{
    return Vector2D(-_x, -_y);
}

Vector2D Vector2D::operator +(const Vector2D &vector) const
{
    return Vector2D( _x + vector._x, _y + vector._y);
}

bool Vector2D::operator <(const Vector2D &vector) const
{
    return (this->X()<vector.X() || (!(this->X() > vector.X()) && (this->Y() < vector.Y())));
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

void Vector2D::normalize()
{
    float magSqrd = _x*_x + _y*_y;
    if(magSqrd > 0.0f){
        float oneOverMag = 1.0 / sqrt(magSqrd);
        _x *= oneOverMag;
        _y *= oneOverMag;
    }
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
    Vector3D v3d(this->_x, this->_y, 0);
    return v3d;
}

b2Vec2 Vector2D::b2vec2()
{
    return b2Vec2(this->_x, this->_y);
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
