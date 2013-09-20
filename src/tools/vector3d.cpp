#include "vector3d.h"
#include "vector2d.h"
#include <math.h>

Vector3D::Vector3D()
{
    x = y = teta = 0;
}

Vector3D::Vector3D(const Vector3D &vector)
{
    x = vector.x; y = vector.y; teta = vector.teta;
}

Vector3D::Vector3D(double nx, double ny, double nteta)
{
    x = nx;    y = ny;    teta = nteta;
}

Vector3D Vector3D::operator =(const Vector3D &vector)
{
    x = vector.x; y = vector.y; teta = vector.teta;
    return *this;
}

bool Vector3D::operator ==(const Vector3D &vector)
{
    return x == vector.x && y == vector.y && teta == vector.teta;
}

bool Vector3D::operator !=(const Vector3D &vector)
{
    return x != vector.x || y != vector.y || teta != vector.teta;
}

void Vector3D::setZero()
{
    x = y = teta = 0.0;
}

Vector3D Vector3D::operator -() const
{
    return Vector3D(-x, -y, -teta);
}

Vector3D Vector3D::operator +(const Vector3D &vector) const
{
    return Vector3D( x + vector.x, y + vector.y, teta + vector.teta);
}

Vector3D Vector3D::operator -(const Vector3D &vector) const
{
    return Vector3D( x - vector.x, y - vector.y, teta - vector.teta);
}

Vector3D Vector3D::operator *(double s)
{
    return Vector3D( x*s, y*s, teta*s);
}

Vector3D Vector3D::operator /(double s)
{
    double oneOverS = 1.0f / s;
    return Vector3D( x*oneOverS, y*oneOverS, teta*oneOverS);
}

Vector3D &Vector3D::operator +=(const Vector3D &vector)
{
    x += vector.x; y += vector.y; teta += vector.teta;
    return *this;
}

Vector3D &Vector3D::operator -=(const Vector3D &vector)
{
    x -= vector.x; y -= vector.y; teta -= vector.teta;
    return *this;
}

Vector3D &Vector3D::operator *=(double s)
{
    x *= s; y *= s; teta *= s;
    return *this;
}

Vector3D &Vector3D::operator /=(double s)
{
    double oneOverS = 1.0f / s;
    x *= oneOverS; y *= oneOverS; teta *= oneOverS;
    return *this;
}

void Vector3D::normalize2D()
{
    double magSqrd = x*x + y*y;
    if(magSqrd > 0.0f){
        double oneOverMag = 1.0 / sqrt(magSqrd);
        x *= oneOverMag;
        y *= oneOverMag;        
    }
}

double Vector3D::lenght2D()
{
    return this->toVector2D().lenght();
}

void Vector3D::correctTeta()
{
    while(teta > M_PI)
        teta -= M_PI;
    while(teta <= -1*M_PI)
        teta += M_PI;
}

Vector2D Vector3D::toVector2D()
{
    Vector2D * v2d = new Vector2D(this->x, this->y);
    return (*v2d);
}

double Vector3D::vector2DMag(const Vector3D &vector)
{
    Vector3D tmp = vector;
    return Vector2D::vectorMag(tmp.toVector2D());
}

double Vector3D::distance2D(const Vector3D &a, const Vector3D &b)
{
    Vector3D tmp_a = a, tmp_b = b;
    return Vector2D::distance(tmp_a.toVector2D(), tmp_b.toVector2D());
}

