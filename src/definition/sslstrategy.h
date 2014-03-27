#ifndef SSLSTRATEGY_H
#define SSLSTRATEGY_H

#include "../general.h"
#include "../referee/SSLReferee.h"

class SSLRole;

class SSLStrategy
{
public:
    SSLStrategy();

    std::string m_name;
    SSLReferee::RefereeState m_refereeCondition;
    std::vector<SSLRole*> m_roleList;

};

#endif // SSLSTRATEGY_H
