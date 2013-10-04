#ifndef MIDFIELDERPOST_H
#define MIDFIELDERPOST_H

#include "SSLPost.h"

class MidfielderPost : public SSLPost
{
public:
    MidfielderPost();
    virtual void run() = 0;

};

#endif // MIDFIELDERPOST_H
