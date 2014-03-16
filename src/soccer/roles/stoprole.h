#ifndef STOPROLE_H
#define STOPROLE_H

#include "sslrole.h"

class StopRole : public SSLRole
{
public:
    StopRole(SSLAgent* agent);

    void run();
};

#endif // STOPROLE_H
