#include "sslrolemanager.h"
#include "../ai/SSLAnalyzer.h"
#include "../ai/SSLGame.h"
#include "roles/goalkeeper.h"

SSLRoleManager* SSLRoleManager::manager_instance = NULL;

SSLRoleManager::SSLRoleManager()
{
//    SSLAgent* agent_0 = SSLGame::getInstance()->agents[0];
//    testRole1 = new GoalKeeper();
//    testRole1->setAgent(agent_0);

//    agent_0->role = testRole1;
//    if(game()->ourTeam()->inFields().size() > 0)
//    {
//        agent_0->robot = SSLGame::getInstance()->ourTeam()->robot[2];
//    }
    spareDefender = new Defender(3, 3);
    spareBlocker = new Blocker(2);
    spareOpponentMarker = new OpponentMarker();
}

SSLRoleManager *SSLRoleManager::getInstance()
{
    if(manager_instance == NULL)
        manager_instance = new SSLRoleManager();
    return manager_instance;
}

void SSLRoleManager::joinAgentAndRole(SSLAgent *agent, SSLRole *role)
{
    try {
        if(agent->isNull())
            throw "This agent is Null and no role can be assigend to";
        agent->role = role;
        role->m_agent = agent;
    }
    catch (const char* mes) {
        cout << "Exception: " << "Role Manager: " << mes << endl;
    }

}

void SSLRoleManager::AssignRole(SSLStrategy *strategy, vector<SSLAgent*> agents)
{
    try {
        if(strategy == NULL) {
            throw "Strategy is NULL!!";
        }

        vector<SSLRole* > roleList = strategy->m_roleList;
        for(int i = roleList.size()-1; i >=0 ; i--) {
            SSLRole* role = roleList[i];
            int min_id = MAX_ID_NUM;
            int goalie_index = -1;
            SSLAgent* goalie_agent = NULL;
            if(role->m_hardness == 0) // goal_keeper
            {
                for(uint j=0; j < agents.size(); j++) {
                    SSLAgent* agent = agents[j];
                    if(agent->isNull())
                        continue;
                    if(agent->getID() == GOALKEPPER_DEFAULT_ID) {
                        goalie_agent = agent;
                        goalie_index = j;
                        break;
                    }
                    if(agent->getID() < min_id) {
                        min_id = agent->getID();
                        goalie_agent = agent;
                        goalie_index = j;
                    }
                }
                if(goalie_agent != NULL) {
                    joinAgentAndRole(goalie_agent, role);
                    agents.erase(agents.begin() + goalie_index);
                    roleList.erase(roleList.begin() + i);
                }
            }
        }

        for(uint i=0; i< roleList.size(); i++) {
            if(agents.empty()) {
                throw "No enough agent";
            }
            SSLRole* role = roleList.at(i);
            Vector2D expPos = role->expectedPosition().to2D();
            float minDist = INFINITY;
            short nearAgentIndex = -1;
            for(uint j=0; j<agents.size(); j++)
            {
                SSLAgent* agent = agents.at(j);
                if(agent->isNull()) {
//                    throw ("agent number " + i + " is null");
                    continue;
                }

                float dist = (agent->robot->Position().to2D() - expPos).lenght();
                if( dist < minDist ) {
                    minDist = dist;
                    nearAgentIndex = j;
                }
            }

            if(nearAgentIndex >= 0) {
                SSLAgent* agent = agents.at(nearAgentIndex);
                joinAgentAndRole(agent, role);
                agents.erase(agents.begin() + nearAgentIndex);
            }

        }
    }
    catch (const char* mes)  {
        cout << "Exception:" << "Role Manager: " << mes << endl;
    }


//    SSLAgent* agent_0 = SSLGame::getInstance()->agents[0];

//    agent_0->role = testRole1;
//    if(game()->ourTeam()->inFields().size() > 0)
//    {
//        agent_0->robot = SSLGame::getInstance()->ourTeam()->robot[0];
//    }
//    agent_0->role =
//    get nearest player from analyzer
//    SSLTeam* our_team = game()->ourTeam();
//    SSLRobot* nearestRobot = analyzer()->nearestPlayer(our_team);
//    if(nearestRobot != NULL)
//    {
//        SSLAgent *nearestAgent = game()->getAgent(nearestRobot->id);
//    }

}

void SSLRoleManager::ArrangeDefense(vector<SSLAgent *> agents)
{

}
