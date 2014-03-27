#ifndef SSLROLEMANAGER_H
#define SSLROLEMANAGER_H

#include "../general.h"
#include "../definition/sslagent.h"
#include "../definition/sslstrategy.h"
#include "roles/defender.h"
#include "roles/blocker.h"
#include "roles/opponentmarker.h"

class SSLGame;
class SSLAnalyzer;

#define roleManager  SSLRoleManager::getInstance()

class SSLRoleManager
{
    static SSLRoleManager* manager_instance;
    SSLRoleManager();

public:
    static SSLRoleManager* getInstance();

    void AssignRole(SSLStrategy *strategy, vector<SSLAgent*> agents);
    void ArrangeDefense(vector<SSLAgent*> agents);

private:
    SSLRole* testRole1;

    Defender* spareDefender;
    Blocker* spareBlocker;
    OpponentMarker* spareOpponentMarker;

    void joinAgentAndRole(SSLAgent* agent, SSLRole* role);

};

#endif // SSLROLEMANAGER_H
