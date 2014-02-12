#ifndef Vector3D_Header_h
#define Vector3D_Header_h

class Vector2D;
class b2Vec3;

class Vector3D
{
    double _x, _y, _teta;
public:
    void setX(double x_);
    void setY(double y_);
    void setTeta(double teta_);
    void set(double x_, double y_, double teta_);
    
    double X() const;
    double Y() const;
    double Teta() const;

    Vector3D();
    Vector3D(const Vector3D &vector);
    Vector3D(double nx, double ny, double nteta);

    Vector3D operator =(const Vector3D &vector);
    bool operator ==(const Vector3D &vector);
    bool operator !=(const Vector3D &vector);
    bool isNull()const;
    void setZero();
    void normalize2D();
    double lenght2D();
    void correctTeta();

    Vector2D normalized2D() const;

    Vector3D operator -() const;
    Vector3D operator +(const Vector3D &vector) const;
    Vector3D operator -(const Vector3D &vector) const;
    Vector3D operator *(double s);
    Vector3D operator /(double s);

    Vector3D &operator +=(const Vector3D &vector);
    Vector3D &operator -=(const Vector3D &vector);
    Vector3D &operator *=(double s);
    Vector3D &operator /=(double s);
//    double operator *(const Vector3D &vector);
    Vector2D to2D();
    b2Vec3 b2vec3();

    static double vector2DMag(const Vector3D  &vector);
    static double distance2D(const Vector3D &a, const Vector3D &b);

};
#endif
