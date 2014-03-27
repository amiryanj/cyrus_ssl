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

#include "../general.h"
#include "../definition/sslstrategy.h"

#define strategyManager  SSLStrategyManager::getInstance()

class SSLStrategyManager
{
    SSLStrategyManager();
    static SSLStrategyManager* manager_instance;

public:
    static SSLStrategyManager* getInstance();
    std::vector<SSLStrategy> strategyList;

    SSLStrategy* updateStrategy(SSLStrategy *strategy);

    void initialStrategyFiles();

private:
    SSLStrategy* normalPlay_1;
    SSLStrategy* offensePlay_1;
    SSLStrategy* defensePlay_1;

    SSLStrategy* ourKickOffFormation_1;
    SSLStrategy* opponentKickOffFormation_1;

    SSLStrategy* ourPenaltyFormation_1;
    SSLStrategy* opponentPenaltyFormation_1;
//    SSLStrategy* opponentPenaltyKick_1;

    SSLStrategy* ourDirectKick_1;
    SSLStrategy* opponentDirectKickFormation_1;
    SSLStrategy* ourIndirectKick_1;
    SSLStrategy* opponentIndirectKickFormation_1;

};

#endif // SSLSTRATEGYMANAGER_H
