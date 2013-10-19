#include "sslrolemanager.h"

SSLRoleManager* SSLRoleManager::manager = NULL;

SSLRoleManager::SSLRoleManager()
{
    analyzer = SSLAnalyzer::getInstance();
}

SSLRoleManager *SSLRoleManager::getInstance()
{
    if(manager == NULL)
        manager = new SSLRoleManager();
    return manager;
}

void SSLRoleManager::assignRole(std::vector<SSLAgent*> agents)
{
    // get nearest player from analyzer

}
