#ifndef SSLSTRATEGY_H
#define SSLSTRATEGY_H

#include "general.h"
#include "definition/SSLPost.h"


class SSLStrategy
{
public:
    SSLStrategy();

    std::string name;
    std::vector<SSLPost> postList;


};

#endif // SSLSTRATEGY_H
