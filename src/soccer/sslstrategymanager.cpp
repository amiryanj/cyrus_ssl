#include "sslstrategymanager.h"
#include "roles/activerole.h"
#include "roles/blocker.h"
#include "roles/defender.h"
#include "roles/goalkeeper.h"
#include "roles/opponentmarker.h"
#include "roles/positionrole.h"
#include "roles/waitpass.h"
#include "roles/waitrebound.h"
//#include "roles/playstarter.h"
//#include "roles/wallstander.h"

#define analyzer    SSLAnalyzer::getInstance()
#define game        SSLGame::getInstance()
#define world       SSLWorldModel::getInstance()

SSLStrategyManager* SSLStrategyManager::manager_instance = NULL;

SSLStrategyManager *SSLStrategyManager::getInstance()
{
    if(manager_instance == NULL)
        manager_instance = new SSLStrategyManager();
    return manager_instance;
}

SSLStrategyManager::SSLStrategyManager()
{
    {
        normalPlay_1 = new SSLStrategy();
        normalPlay_1->m_name = "normalPlay_1";
        SSLRole* r[6] = {
            new ActiveRole(),
            new GoalKeeper(),
            new Defender(1, 3),
            new Defender(2, 3),
            new Defender(3, 3),
            new WaitPass()
        };
        for (int i=0; i<6; i++) {
            normalPlay_1->m_roleList.push_back(r[i]);
        }
    }


    {
        offensePlay_1 = new SSLStrategy();
        offensePlay_1->m_name = "offensePlay_1";
        SSLRole* r[6] = {
            new ActiveRole(),
            new GoalKeeper(),
            new WaitPass(),
            new Defender(1, 2),
            new Defender(2, 2),
            new WaitPass()
        };
        for (int i=0; i<6; i++) {
            offensePlay_1->m_roleList.push_back(r[i]);
        }
    }


    {
        defensePlay_1 = new SSLStrategy();
        defensePlay_1->m_name = "defensePlay_1";
        SSLRole* r[6] = {
            new ActiveRole(),
            new GoalKeeper(),
            new Defender(1, 2),
            new Defender(2, 2),
            new Blocker(),
            new Defender(3, 3)
        };
        for (int i=0; i<6; i++) {
            defensePlay_1->m_roleList.push_back(r[i]);
        }
    }


    {
        kickOffFormation_1 = new SSLStrategy;
        kickOffFormation_1->m_name = "KickOffFormation_1";
        SSLRole* r[6] = {
            new ActiveRole(),
            new GoalKeeper(),
            new WaitPass(),
            new Defender(1, 2),
            new Defender(2, 2),
            new WaitPass()
        };
        for (int i=0; i<6; i++) {
            kickOffFormation_1->m_roleList.push_back(r[i]);
        }
    }


    {
        opponentKickOffFormation_1 = new SSLStrategy();
        opponentKickOffFormation_1->m_name = "opponentKickOffFormation_1";
        SSLRole* r[6] = {
            new ActiveRole(),
            new Blocker(),
            new GoalKeeper(),
            new Defender(1, 2),
            new Defender(2, 2),
            new WaitPass()
        };
        for (int i=0; i<6; i++) {
            opponentKickOffFormation_1->m_roleList.push_back(r[i]);
        }
    }


    {
        ourPenaltyFormation_1 = new SSLStrategy();
        ourPenaltyFormation_1->m_name = "ourPenaltyFormation_1";
        SSLRole* r[6] = {
            r[0] = new ActiveRole(),
            r[1] = new GoalKeeper(),
            r[2] = new Defender(1, 2),
            r[3] = new Defender(2, 2),
            r[4] = new WaitPass(),
            r[5] = new Defender(3, 3)
        };
        for (int i=0; i<6; i++) {
            ourPenaltyFormation_1->m_roleList.push_back(r[i]);
        }
    }


    {
        opponentPenaltyFormation_1 = new SSLStrategy();
        opponentPenaltyFormation_1->m_name = "opponentPenaltyFormation_1";
        SSLRole* r[6] = {
            new GoalKeeper(),
            new WaitPass(),
            new WaitPass(),
            new WaitPass(),
            new Defender(1, 1),
            new Defender(2, 2)
        };
        for (int i=0; i<6; i++) {
            opponentPenaltyFormation_1->m_roleList.push_back(r[i]);
        }
    }


    {
        ourFreeKick_1 = new SSLStrategy();
        ourFreeKick_1->m_name = "ourDirectKick_1";
        SSLRole* r[6] = {
            r[0] = new ActiveRole(),
            r[1] = new GoalKeeper(),
            r[2] = new WaitPass(),
            r[3] = new Defender(1, 2),
            r[4] = new Defender(2, 2),
            r[5] = new WaitPass()
        };
        for (int i=0; i<6; i++) {
            ourFreeKick_1->m_roleList.push_back(r[i]);
        }
    }


    {
        opponentFreeKickFormation_1 = new SSLStrategy();
        opponentFreeKickFormation_1->m_name = "opponentDirectKickFormation_1";
        SSLRole* r[6] = {
            r[0] = new GoalKeeper(),
            r[1] = new WaitPass(),
            r[2] = new WaitPass(),
            r[3] = new Defender(1, 2),
            r[4] = new Defender(2, 2),
            r[5] = new WaitPass()
        };
        for (int i=0; i<6; i++) {
            opponentFreeKickFormation_1->m_roleList.push_back(r[i]);
        }
    }

}

SSLStrategy *SSLStrategyManager::updateStrategy(SSLStrategy *strategy)
{
    if(analyzer->isGameRunning()) {
        strategy = normalPlay_1;
    }

//    else if(world->m_refereeState == SSLReferee::Stop) {

//    }

    else if(analyzer->isOurKickOffPosition() || analyzer->isOurKickOffKick()) {
        strategy = kickOffFormation_1;
    }

    else if(analyzer->isOpponentKickOffPosition() || analyzer->isOpponentKickOffKick()) {
        strategy = opponentKickOffFormation_1;
    }

    else if(analyzer->isOurPenaltyPosition() || analyzer->isOurPenaltyKick()) {
        strategy = ourPenaltyFormation_1;
    }

    else if(analyzer->isOpponentPenaltyPosition() || analyzer->isOpponentPenaltyKick()) {
        strategy = opponentPenaltyFormation_1;
    }

    else if(analyzer->isOurDirectKick() || analyzer->isOurIndirectKick()) {
        strategy = ourFreeKick_1;
    }

    else if(analyzer->isOpponentDirectKick() || analyzer->isOpponentIndirectKick()) {
        strategy = opponentFreeKickFormation_1;
    }

    else {
        // unknown state: taka a urgent strategy

        // for test:
        strategy = normalPlay_1;
//        strategy = ourKickOffFormation_1;
    }

    return strategy;
}
