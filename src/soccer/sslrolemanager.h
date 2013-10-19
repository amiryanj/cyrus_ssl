#ifndef SSLROLEMANAGER_H
#define SSLROLEMANAGER_H

#include "general.h"
#include "definition/sslagent.h"
#include "ai/SSLAnalyzer.h"

class SSLRoleManager
{
    static SSLRoleManager* manager;
    SSLRoleManager();

public:
    static SSLRoleManager* getInstance();

    void assignRole(std::vector<SSLAgent*> agents);

private:
    SSLAnalyzer *analyzer;

};

#endif // SSLROLEMANAGER_H
