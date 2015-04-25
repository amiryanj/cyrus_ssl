#ifndef _Vector2D_H
#define _Vector2D_H

#include <iosfwd>
#include <ostream>

class Vector3D;
class LineSegment;
#ifdef _USE_QT_
class QVector3D;
class QVector2D;
class QPointF;
#endif
struct b2Vec3;
struct b2Vec2;

class Vector2D
{
    float _x, _y;
public:
    void set(float x_, float y_);
    void setX(float x_);
    void setY(float y_);

    float X() const;
    float Y() const;

    Vector2D();
    Vector2D(const Vector2D &vector);
    Vector2D(float nx, float ny);

    Vector2D operator =(const Vector2D &vector);
    bool operator ==(const Vector2D &vector) const;
    bool operator !=(const Vector2D &vector) const;
    void normalize();
    Vector2D normalized() const;
    bool isInf() const;
    void setZero();
    void rotate(float radian_rot);
    float lenght() const;
    float arctan() const;
    float distToLine(const LineSegment &ls) const;

    Vector2D operator -() const;
    Vector2D operator +(const Vector2D &vector) const;
    Vector2D operator -(const Vector2D &vector) const;
    Vector2D operator *(float s);
    Vector2D operator /(float s);

    Vector2D &operator +=(const Vector2D &vector);
    Vector2D &operator -=(const Vector2D &vector);
    Vector2D &operator *=(float s);
    Vector2D &operator /=(float s);
    float operator *(const Vector2D &vector);

    Vector3D to3D();

#ifdef _USE_BOX2D_
    Vector2D(b2Vec2 vec);
    b2Vec2 toB2vec2();
    b2Vec3 toB2vec3();
#endif

#ifdef _USE_QT_
    Vector2D(QVector2D &qvec);
    Vector2D(QPointF qpnt);
    QVector3D toQvec3D();
    QVector2D toQvec2D();
    QPointF toQpoint();
#endif

    void print(std::ostream &stream);

//    Vector2D crossProduct(const Vector2D &a, const Vector2D &b);
    static float vectorMag(const Vector2D  &vector);
    static float distance(const Vector2D &a, const Vector2D &b);
    static Vector2D unitVector(float direction_rad);

    static float dot(const Vector2D& a, const Vector2D& b);
    static float angleBetween(const Vector2D& a, const Vector2D& b);

    bool operator <(const Vector2D &vector) const;

};

std::ostream& operator<< (std::ostream &out, Vector2D &p);
#endif // _Vector2D_H
