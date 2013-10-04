#ifndef SSLPOST_H
#define SSLPOST_H

#include "../SSLRole.h"

class SSLPost
{
public:
    SSLPost();
    virtual void run() = 0;

    SSLRole role;
};

#endif // SSLPOST_H
