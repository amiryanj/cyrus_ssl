#ifndef SSLOBJECT_H
#define SSLOBJECT_H

//#include <boost/math/complex.hpp>
#include <QVector3D>

enum SSL_OBJECT_TYPE {BALL_OBJECT, ROBOT_OBJECT};

class SSLObject
{
public:
    SSLObject();

protected:
    QVector3D position;
    QVector3D speed;

    SSL_OBJECT_TYPE type;
    double radius;
    double mass;
};

#endif // SSLOBJECT_H
