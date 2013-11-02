#ifndef SSLSTRATEGY_H
#define SSLSTRATEGY_H

#include "general.h"
#include "soccer/roles/SSLRole.h"

class SSLStrategy
{
public:
    SSLStrategy();

    std::string name;
    std::vector<SSLRole> postList;


};

#endif // SSLSTRATEGY_H
