#ifndef _Vector3D_H
#define _Vector3D_H

class Vector2D;
class QVector3D;
class QVector2D;
struct b2Vec3;
struct b2Vec2;

class Vector3D
{
    float _x, _y, _teta;
public:
    void setX(float x_);
    void setY(float y_);
    void setTeta(float teta_);
    void set(float x_, float y_, float teta_);
    
    float X() const;
    float Y() const;
    float Teta() const;

    Vector3D();
    Vector3D(const Vector3D &vector);
    Vector3D(const Vector2D &point, float nteta);
    Vector3D(float nx, float ny, float nteta);

    Vector3D operator =(const Vector3D &vector);
    bool operator ==(const Vector3D &vector);
    bool operator !=(const Vector3D &vector);
    bool isNull() const;
    bool isInf() const;
    void normalize2D();
    void rotate(float radianAngle);
    float lenght2D() const;
    void correctTeta();
    Vector3D& setZero();

    Vector2D getNormalized2D() const;

    Vector3D operator -() const;
    Vector3D operator +(const Vector3D &vector) const;
    Vector3D operator -(const Vector3D &vector) const;
    Vector3D operator *(float s) const;
    Vector3D operator /(float s) const;

    Vector3D &operator +=(const Vector3D &vector);
    Vector3D &operator -=(const Vector3D &vector);
    Vector3D &operator *=(float s);
    Vector3D &operator /=(float s);
//    float operator *(const Vector3D &vector);
    Vector2D to2D() const;

#ifdef _USE_BOX2D_
    Vector3D(b2Vec3 vec);
    b2Vec3 toB2vec3();
    b2Vec2 toB2vec2();
#endif

#ifdef _USE_QT_
    Vector3D(QVector3D qvec);
    QVector3D toQvec3D();
    QVector2D toQvec2D();
#endif

    Vector3D dotProduct(Vector3D &b);

    static float vector2DMag(const Vector3D  &vector);
    static float distance2D(const Vector3D &a, const Vector3D &b);

};
#endif // _Vector3D_H
