#include "sslrolemanager.h"
#include "../ai/SSLAnalyzer.h"
#include "../ai/SSLGame.h"

SSLRoleManager* SSLRoleManager::manager = NULL;

SSLRoleManager::SSLRoleManager()
{    
}

SSLRoleManager *SSLRoleManager::getInstance()
{
    if(manager == NULL)
        manager = new SSLRoleManager();
    return manager;
}

SSLAnalyzer *SSLRoleManager::analyzer()
{
    return SSLAnalyzer::getInstance();
}

SSLGame *SSLRoleManager::game()
{
    return SSLGame::getInstance();
}

void SSLRoleManager::assignRole(const SSLStrategy &strategy, std::vector<SSLAgent*> agents)
{
    SSLAgent* agent_0 = SSLGame::getInstance()->agents[0];
//    agent_0->role =
//    get nearest player from analyzer
//    SSLTeam* our_team = game()->ourTeam();
//    SSLRobot* nearestRobot = analyzer()->nearestPlayer(our_team);
//    if(nearestRobot != NULL)
//    {
//        SSLAgent *nearestAgent = game()->getAgent(nearestRobot->id);
//    }


}
