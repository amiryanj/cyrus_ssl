#ifndef Vector3D_Header_h
#define Vector3D_Header_h

class Vector2D;

class Vector3D
{
public:
    double x, y, teta;
    
    Vector3D();
    Vector3D(const Vector3D &vector);
    Vector3D(double nx, double ny, double nteta);

    Vector3D operator =(const Vector3D &vector);
    bool operator ==(const Vector3D &vector);
    bool operator !=(const Vector3D &vector);
    void setZero();
    void normalize2D();
    double lenght2D();
    void correctTeta();

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
    Vector2D toVector2D();

    static double vector2DMag(const Vector3D  &vector);
    static double distance2D(const Vector3D &a, const Vector3D &b);

};
#endif
