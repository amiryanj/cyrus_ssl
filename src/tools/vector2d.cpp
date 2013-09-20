#include "vector2d.h"
#include "vector3d.h"
#include <math.h>

Vector2D::Vector2D()
{
    x = y = 0;
}

Vector2D::Vector2D(const Vector2D &vector)
{
    x = vector.x; y = vector.y;
}

Vector2D::Vector2D(double nx, double ny)
{
    x = nx;    y = ny;
}

Vector2D Vector2D::operator =(const Vector2D &vector)
{
    x = vector.x; y = vector.y;
    return *this;
}

bool Vector2D::operator ==(const Vector2D &vector)
{
    return x == vector.x && y == vector.y;
}

bool Vector2D::operator !=(const Vector2D &vector)
{
    return x != vector.x || y != vector.y;
}

void Vector2D::setZero()
{
    x = y = 0.0;
}

double Vector2D::lenght()
{
    return sqrt(x*x + y*y);
}

Vector2D Vector2D::operator -() const
{
    return Vector2D(-x, -y);
}

Vector2D Vector2D::operator +(const Vector2D &vector) const
{
    return Vector2D( x + vector.x, y + vector.y);
}

Vector2D Vector2D::operator -(const Vector2D &vector) const
{
    return Vector2D( x - vector.x, y - vector.y);
}

Vector2D Vector2D::operator *(double s)
{
    return Vector2D( x*s, y*s);
}

Vector2D Vector2D::operator /(double s)
{
    double oneOverS = 1.0f / s;
    return Vector2D( x*oneOverS, y*oneOverS);
}

Vector2D &Vector2D::operator +=(const Vector2D &vector)
{
    x += vector.x; y += vector.y;
    return *this;
}

Vector2D &Vector2D::operator -=(const Vector2D &vector)
{
    x -= vector.x; y -= vector.y;
    return *this;
}

Vector2D &Vector2D::operator *=(double s)
{
    x *= s; y *= s;
    return *this;
}

Vector2D &Vector2D::operator /=(double s)
{
    double oneOverS = 1.0f / s;
    x *= oneOverS; y *= oneOverS;
    return *this;
}

void Vector2D::normalize()
{
    double magSqrd = x*x + y*y;
    if(magSqrd > 0.0f){
        double oneOverMag = 1.0 / sqrt(magSqrd);
        x *= oneOverMag;
        y *= oneOverMag;
    }
}

double Vector2D::operator *(const Vector2D &vector)
{
    return (x * vector.x) + (y * vector.y);
}

Vector3D Vector2D::toVector3D()
{
    Vector3D *v3d = new Vector3D(this->x, this->y, 0);
    return (*v3d);
}

double Vector2D::vectorMag(const Vector2D &vector)
{
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}

double Vector2D::distance(const Vector2D &a, const Vector2D &b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}


