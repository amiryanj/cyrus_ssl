#ifndef SSLROLEMANAGER_H
#define SSLROLEMANAGER_H

#include "../general.h"
#include "../definition/sslagent.h"
#include "../definition/sslstrategy.h"

class SSLGame;
class SSLAnalyzer;

class SSLRoleManager
{
    static SSLRoleManager* manager;
    SSLRoleManager();

public:
    static SSLRoleManager* getInstance();

    void assignRole(const SSLStrategy &strategy, std::vector<SSLAgent*> agents);

private:
    SSLAnalyzer* analyzer();
    SSLGame* game();

};

#endif // SSLROLEMANAGER_H
