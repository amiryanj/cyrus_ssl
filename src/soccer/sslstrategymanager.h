#ifndef SSLSTRATEGYMANAGER_H
#define SSLSTRATEGYMANAGER_H

/*
 * the duty of this manager is to
 * 1. read strategy script files, translate them, make related objects and store them
 * 2. each time according to game result, referee state, coach desires, ... decide a
 *      strategy and active it. (by state-machine-based behavior)
 * 3. assign performancec value to strategies (and save in config file) to use experiments
 *
 */

#include "general.h"
#include "definition/sslstrategy.h"

class SSLStrategyManager
{
    SSLStrategyManager();
    static SSLStrategyManager* manager;

public:
    static SSLStrategyManager* getInstance();
    std::vector<SSLStrategy> strategyList;

    void updateStrategy(SSLStrategy &strategy);

    void initialStrategyFiles();

private:


};

#endif // SSLSTRATEGYMANAGER_H
