#ifndef _ACTIVEROLE_H
#define _ACTIVEROLE_H

#include "sslrole.h"

class ActiveRole : public SSLRole
{
public:
    ActiveRole();

    void run();
    Vector2D expectedPosition();

private:

};

#endif // _ACTIVEROLE_H
