#ifndef Vector2D_Header_h
#define Vector2D_Header_h

class Vector3D;
class b2Vec2;

class Vector2D
{
    double _x, _y;
public:
    void set(double x_, double y_);
    void setX(double x_);
    void setY(double y_);

    double X() const;
    double Y() const;

    Vector2D();
    Vector2D(const Vector2D &vector);
    Vector2D(double nx, double ny);
    Vector2D(b2Vec2 vec);

    Vector2D operator =(const Vector2D &vector);
    bool operator ==(const Vector2D &vector);
    bool operator !=(const Vector2D &vector);
    void normalize();
    Vector2D normalized() const;
    bool isInf() const;
    void setZero();
    void rotate(double radian_rot);
    double lenght();
    double arctan();

    Vector2D operator -() const;
    Vector2D operator +(const Vector2D &vector) const;
    Vector2D operator -(const Vector2D &vector) const;
    Vector2D operator *(double s);
    Vector2D operator /(double s);

    Vector2D &operator +=(const Vector2D &vector);
    Vector2D &operator -=(const Vector2D &vector);
    Vector2D &operator *=(double s);
    Vector2D &operator /=(double s);
    double operator *(const Vector2D &vector);

    Vector3D to3D();
    b2Vec2 b2vec2();

//    Vector2D crossProduct(const Vector2D &a, const Vector2D &b);
    static double vectorMag(const Vector2D  &vector);
    static double distance(const Vector2D &a, const Vector2D &b);

};

#endif
