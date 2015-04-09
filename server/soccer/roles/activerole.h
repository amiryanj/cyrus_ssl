#ifndef _ACTIVEROLE_H
#define _ACTIVEROLE_H

#include "../sslrole.h"

class ActiveRole : public SSLRole
{
public:
    ActiveRole(int index_ = 1);

    void run();
    Vector3D expectedPosition();

private:
    Vector3D myTarget();

    int m_index;


};

#endif // _ACTIVEROLE_H
