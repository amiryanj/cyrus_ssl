#ifndef ATTACKERPOST_H
#define ATTACKERPOST_H

#include "SSLPost.h"

class AttackerPost : public SSLPost
{
public:
    AttackerPost();
    virtual void run() = 0;
};

#endif // ATTACKERPOST_H
