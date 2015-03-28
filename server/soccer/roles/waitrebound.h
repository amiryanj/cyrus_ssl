#ifndef _WAITREBOUND_H
#define _WAITREBOUND_H

#include "../sslrole.h"
#include "../sslagent.h"

class WaitRebound : public SSLRole
{

public:
    WaitRebound();

    void run();

    Vector3D getBestPosition() const;
    void setBestPosition(const Vector3D &value);

    Vector3D expectedPosition();

private:
    Vector3D m_bestPosition;
};

#endif // _WAITREBOUND_H
