#include "vector3d.h"
#include "vector2d.h"
#include <math.h>
#include <Box2D/Common/b2Math.h>
#include "sslmath.h"

Vector3D::Vector3D()
{
    _x = _y = _teta = 0;
}

Vector3D::Vector3D(const Vector3D &vector)
{
    _x = vector._x; _y = vector._y; _teta = vector._teta;
}

Vector3D::Vector3D(const Vector2D &point, float nteta)
{
    _x = point.X();  _y = point.Y();  _teta = nteta;
}

Vector3D::Vector3D(float nx, float ny, float nteta)
{
    _x = nx;    _y = ny;    _teta = nteta;
}

Vector3D Vector3D::operator =(const Vector3D &vector)
{
    _x = vector._x; _y = vector._y; _teta = vector._teta;
    return *this;
}

bool Vector3D::operator ==(const Vector3D &vector)
{
    return _x == vector._x && _y == vector._y && _teta == vector._teta;
}

bool Vector3D::operator !=(const Vector3D &vector)
{
    return _x != vector._x || _y != vector._y || _teta != vector._teta;
}

bool Vector3D::isNull() const
{
    if(_x == 0 && _y == 0 && _teta == 0)
        return true;
    return false;
}

bool Vector3D::isInf() const
{
    if(_x == INFINITY || _y == INFINITY)
        return true;
    return false;
}

Vector3D& Vector3D::setZero()
{
    _x = _y = _teta = 0.0;
    return (*this);
}

Vector3D Vector3D::operator -() const
{
    return Vector3D(-_x, -_y, -_teta);
}

Vector3D Vector3D::operator +(const Vector3D &vector) const
{
    Vector3D res;
    res.set(_x + vector._x, _y + vector._y, _teta + vector._teta);
    res.setTeta(SSL::continuousRadian(res.Teta(), -M_PI));
    return res;
}

Vector3D Vector3D::operator -(const Vector3D &vector) const
{
    Vector3D res;
    res.set(_x - vector._x, _y - vector._y, _teta - vector._teta);
    res.setTeta(SSL::continuousRadian(res.Teta(), -M_PI));
    return res;
}

Vector3D Vector3D::operator *(float s) const
{
    return Vector3D( _x*s, _y*s, _teta*s);
}

Vector3D Vector3D::operator /(float s) const
{
    float oneOverS = 1.0f / s;
    return Vector3D( _x*oneOverS, _y*oneOverS, _teta*s);
}

Vector3D &Vector3D::operator +=(const Vector3D &vector)
{
    _x += vector._x; _y += vector._y; _teta += vector._teta;
    return *this;
}

Vector3D &Vector3D::operator -=(const Vector3D &vector)
{
    _x -= vector._x; _y -= vector._y; _teta -= vector._teta;
    _teta = SSL::continuousRadian(_teta, -M_PI);
    return *this;
}

Vector3D &Vector3D::operator *=(float s)
{
    _x *= s; _y *= s; _teta *= s;
    return *this;
}

Vector3D &Vector3D::operator /=(float s)
{
    float oneOverS = 1.0f / s;
    _x *= oneOverS; _y *= oneOverS; _teta *= oneOverS;
    return *this;
}

void Vector3D::normalize2D()
{
    float magSqrd = _x*_x + _y*_y;
    if(magSqrd > 0.0f){
        float oneOverMag = 1.0 / sqrt(magSqrd);
        _x *= oneOverMag;
        _y *= oneOverMag;
    }
}

void Vector3D::rotate(float radianAngle)
{
    double new_x, new_y;
    new_x = _x * cos(radianAngle) - _y * sin(radianAngle);
    new_y = _x * sin(radianAngle) + _y * cos(radianAngle);
    _x = new_x;
    _y = new_y;
    _teta = _teta;

}

float Vector3D::lenght2D()
{
    return this->to2D().lenght();
}

void Vector3D::correctTeta()
{
    while(_teta > M_PI)
        _teta -= M_PI;
    while(_teta <= -1*M_PI)
        _teta += M_PI;
}

Vector2D Vector3D::normalized2D() const
{
    Vector2D __tmp;
    __tmp.set(this->X(), this->Y());

    return __tmp.normalized();
}

Vector2D Vector3D::to2D()
{
    Vector2D v2d(this->X(), this->Y());
    return v2d;
}

b2Vec3 Vector3D::b2vec3()
{
    return b2Vec3(this->_x, this->_y, this->_teta);
}

Vector3D Vector3D::dotProduct(Vector3D &b)
{
    Vector3D temp;
    temp.setX(this->_x * b._x);    temp.setY(this->_y * b._y);    temp.setTeta(this->_teta * b._teta);
    return temp;
}

float Vector3D::vector2DMag(const Vector3D &vector)
{
    Vector3D tmp = vector;
    return Vector2D::vectorMag(tmp.to2D());
}

float Vector3D::distance2D(const Vector3D &a, const Vector3D &b)
{
    Vector3D tmp_a = a, tmp_b = b;
    return Vector2D::distance(tmp_a.to2D(), tmp_b.to2D());
}

void Vector3D::setX(float x_)
{
    this->_x = x_;
}

void Vector3D::setY(float y_)
{
    this->_y = y_;
}

void Vector3D::setTeta(float teta_)
{
    this->_teta = teta_;
}

void Vector3D::set(float x_, float y_, float teta_)
{
    _x = x_;  _y = y_; _teta = teta_;
}

float Vector3D::X() const
{
    return this->_x;
}

float Vector3D::Y() const
{
    return this->_y;
}

float Vector3D::Teta() const
{
    return this->_teta;
}
