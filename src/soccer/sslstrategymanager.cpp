#include "sslstrategymanager.h"
#include "roles/activerole.h"
#include "roles/blocker.h"
#include "roles/defender.h"
#include "roles/goalkeeper.h"
#include "roles/opponentmarker.h"
#include "roles/playstarter.h"
#include "roles/positionrole.h"
#include "roles/waitpass.h"
#include "roles/waitrebound.h"
#include "roles/wallstander.h"

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
        SSLRole* r[6];
        r[0] = new ActiveRole();
        r[1] = new GoalKeeper();
        r[2] = new Defender(1, 3);
        r[3] = new Defender(2, 3);
        r[4] = new Defender(3, 3);
        r[5] = new WaitRebound();
        for (int i=0; i<6; i++) {
            normalPlay_1->m_roleList.push_back(r[i]);
        }
    }


    {
        offensePlay_1 = new SSLStrategy();
        offensePlay_1->m_name = "offensePlay_1";
        SSLRole* r[6];
        r[0] = new ActiveRole();
        r[1] = new GoalKeeper();
        r[2] = new WaitPass();
        r[3] = new Defender(1, 2);
        r[4] = new Defender(2, 2);
        r[5] = new WaitRebound();
        for (int i=0; i<6; i++) {
            offensePlay_1->m_roleList.push_back(r[i]);
        }
    }


    {
        defensePlay_1 = new SSLStrategy();
        defensePlay_1->m_name = "defensePlay_1";
        SSLRole* r[6];
        r[0] = new ActiveRole();
        r[1] = new GoalKeeper();
        r[2] = new Defender(1, 2);
        r[3] = new Defender(2, 2);
        r[4] = new OpponentMarker();
        r[5] = new Defender(3, 3);
        for (int i=0; i<6; i++) {
            defensePlay_1->m_roleList.push_back(r[i]);
        }
    }


    {
        ourKickOffFormation_1 = new SSLStrategy;
        ourKickOffFormation_1->m_name = "ourKickOffFormation_1";
        SSLRole* r[6];
        r[0] = new PlayStarter();
        r[1] = new GoalKeeper();
        r[2] = new WaitRebound();
        r[3] = new Defender(1, 2);
        r[4] = new Defender(2, 2);
        r[5] = new WaitRebound();
        for (int i=0; i<6; i++) {
            ourKickOffFormation_1->m_roleList.push_back(r[i]);
        }
    }


    {
        opponentKickOffFormation_1 = new SSLStrategy();
        opponentKickOffFormation_1->m_name = "opponentKickOffFormation_1";
        SSLRole* r[6];
        r[0] = new WallStander();
        r[1] = new WallStander();
        r[2] = new GoalKeeper();
        r[3] = new Defender(1, 2);
        r[4] = new Defender(2, 2);
        r[5] = new WaitRebound();
        for (int i=0; i<6; i++) {
            opponentKickOffFormation_1->m_roleList.push_back(r[i]);
        }
    }


    {
        ourPenaltyFormation_1 = new SSLStrategy();
        ourPenaltyFormation_1->m_name = "ourPenaltyFormation_1";
        SSLRole* r[6];
        r[0] = new PlayStarter();
        r[1] = new GoalKeeper();
        r[2] = new Defender(1, 2);
        r[3] = new Defender(2, 2);
        r[4] = new WaitRebound();
        r[5] = new Defender(3, 3);
        for (int i=0; i<6; i++) {
            ourPenaltyFormation_1->m_roleList.push_back(r[i]);
        }
    }


    {
        opponentPenaltyFormation_1 = new SSLStrategy();
        opponentPenaltyFormation_1->m_name = "opponentPenaltyFormation_1";
        SSLRole* r[6];
        r[0] = new GoalKeeper();
        r[1] = new WaitRebound();
        r[2] = new WaitRebound();
        r[3] = new WaitRebound();
        r[4] = new Defender(1, 1);
        r[5] = new Defender(2, 2);
        for (int i=0; i<6; i++) {
            opponentPenaltyFormation_1->m_roleList.push_back(r[i]);
        }
    }


    {
        ourDirectKick_1 = new SSLStrategy();
        ourDirectKick_1->m_name = "ourDirectKick_1";
        SSLRole* r[6];
        r[0] = new PlayStarter();
        r[1] = new GoalKeeper();
        r[2] = new WaitRebound();
        r[3] = new Defender(1, 2);
        r[4] = new Defender(2, 2);
        r[5] = new WaitRebound();
        for (int i=0; i<6; i++) {
            ourDirectKick_1->m_roleList.push_back(r[i]);
        }
    }


    {
        opponentDirectKickFormation_1 = new SSLStrategy();
        opponentDirectKickFormation_1->m_name = "opponentDirectKickFormation_1";
        SSLRole* r[6];
        r[0] = new GoalKeeper();
        r[1] = new WaitRebound();
        r[2] = new WaitRebound();
        r[3] = new Defender(1, 2);
        r[4] = new Defender(2, 2);
        r[5] = new WaitRebound();
        for (int i=0; i<6; i++) {
            opponentDirectKickFormation_1->m_roleList.push_back(r[i]);
        }
    }


    {
        ourIndirectKick_1 = new SSLStrategy();
        ourIndirectKick_1->m_name = "ourIndirectKick_1";
        SSLRole* r[6];
        r[0] = new PlayStarter();
        r[1] = new GoalKeeper();
        r[2] = new WaitRebound();
        r[3] = new Defender(1, 2);
        r[4] = new Defender(2, 2);
        r[5] = new WaitRebound();
        for (int i=0; i<6; i++) {
            ourIndirectKick_1->m_roleList.push_back(r[i]);
        }
    }


    {

        opponentIndirectKickFormation_1 = new SSLStrategy();
        opponentIndirectKickFormation_1->m_name = "opponentIndirectKickFormation_1";
        SSLRole* r[6];
        r[0] = new GoalKeeper();
        r[1] = new WaitRebound();
        r[2] = new WaitRebound();
        r[3] = new Defender(1, 2);
        r[4] = new Defender(2, 2);
        r[5] = new WaitRebound();
        for (int i=0; i<6; i++) {
            opponentIndirectKickFormation_1->m_roleList.push_back(r[i]);
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
        strategy = ourKickOffFormation_1;
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

    else if(analyzer->isOurDirectKick()) {
        strategy = ourDirectKick_1;
    }

    else if(analyzer->isOpponentDirectKick()) {
        strategy = opponentDirectKickFormation_1;
    }

    else if(analyzer->isOurIndirectKick()) {
        strategy = ourIndirectKick_1;
    }

    else if(analyzer->isOpponentIndirectKick()) {
        strategy = opponentIndirectKickFormation_1;
    }

    else {
        // unknown state: taka a urgent strategy

        // for test:
        strategy = normalPlay_1;
//        strategy = ourKickOffFormation_1;
    }

    return strategy;
}
