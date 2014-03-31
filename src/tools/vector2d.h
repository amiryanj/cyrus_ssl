#ifndef _Vector2D_H
#define _Vector2D_H

class Vector3D;
class b2Vec2;

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
    Vector2D(b2Vec2 vec);

    Vector2D operator =(const Vector2D &vector);
    bool operator ==(const Vector2D &vector);
    bool operator !=(const Vector2D &vector);
    void normalize();
    Vector2D normalized() const;
    bool isInf() const;
    void setZero();
    void rotate(float radian_rot);
    float lenght();
    float arctan();

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
    b2Vec2 b2vec2();

//    Vector2D crossProduct(const Vector2D &a, const Vector2D &b);
    static float vectorMag(const Vector2D  &vector);
    static float distance(const Vector2D &a, const Vector2D &b);

    bool operator <(const Vector2D &vector) const;
};

#endif // _Vector2D_H
