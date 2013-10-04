#ifndef DEFENDERPOST_H
#define DEFENDERPOST_H

#include "SSLPost.h"

class DefenderPost : public SSLPost
{
public:
    DefenderPost();
    virtual void run() = 0;
};

#endif // DEFENDERPOST_H
