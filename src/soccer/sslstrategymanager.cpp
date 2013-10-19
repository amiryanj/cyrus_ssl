#include "sslstrategymanager.h"

SSLStrategyManager* SSLStrategyManager::manager = NULL;

SSLStrategyManager::SSLStrategyManager()
{
}

SSLStrategyManager *SSLStrategyManager::getInstance()
{
    if(manager == NULL)
        manager = new SSLStrategyManager();
    return manager;
}

void SSLStrategyManager::updateStrategy(SSLStrategy &strategy)
{

}
