#ifndef Vector3D_Header_h
#define Vector3D_Header_h

class Vector2D;
class b2Vec3;

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
    Vector3D(float nx, float ny, float nteta);

    Vector3D operator =(const Vector3D &vector);
    bool operator ==(const Vector3D &vector);
    bool operator !=(const Vector3D &vector);
    bool isNull() const;
    bool isInf() const;
    void setZero();
    void normalize2D();
    void rotate(float radianAngle);
    float lenght2D();
    void correctTeta();

    Vector2D normalized2D() const;

    Vector3D operator -() const;
    Vector3D operator +(const Vector3D &vector) const;
    Vector3D operator -(const Vector3D &vector) const;
    Vector3D operator *(float s);
    Vector3D operator /(float s);

    Vector3D &operator +=(const Vector3D &vector);
    Vector3D &operator -=(const Vector3D &vector);
    Vector3D &operator *=(float s);
    Vector3D &operator /=(float s);
//    float operator *(const Vector3D &vector);
    Vector2D to2D();
    b2Vec3 b2vec3();

    Vector3D dotProduct(Vector3D &b);

    static float vector2DMag(const Vector3D  &vector);
    static float distance2D(const Vector3D &a, const Vector3D &b);

};
#endif
