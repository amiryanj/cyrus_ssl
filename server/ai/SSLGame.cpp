#include "SSLGame.h"

#include "SSLWorldModel.h"
#include "../soccer/sslstrategymanager.h"
#include "../soccer/sslstrategy.h"
#include "../soccer/sslagent.h"
#include "../soccer/sslrolemanager.h"

SSLGame* SSLGame::game_instance = NULL;

SSLGame *SSLGame::getInstance()
{
    assert(game_instance != NULL);
    return game_instance;
}

SSLGame *SSLGame::getInstance(Color set_our_color, Side set_our_side)
{
    assert(game_instance == NULL);
    game_instance = new SSLGame(set_our_color, set_our_side);
    return game_instance;
}

SSLGame::SSLGame(Color ourC, Side ourS)
{    
    SetColor_Side(ourC, ourS);
    for(int i=0; i<MAX_TEAM_PLAYER; i++) {
        SSLAgent* agent_ = new SSLAgent();
        m_agents.push_back(agent_);
    }
    currentStrategy = NULL;
}

void SSLGame::SetColor_Side(Color ourC, Side ourS)
{
    m_ourColor = ourC;
    m_ourSide = ourS;
}

void SSLGame::check()
{
    // TODO
    game_running_counter ++;
//    cout << "Decision (SSLGame) is running" << endl;
    bool changeInAgents = false;
    updateAgents(changeInAgents);

    SSLStrategy* newStrategy = NULL;
    newStrategy = strategyManager->updateStrategy(currentStrategy);
//    if(newStrategy != currentStrategy || changeInAgents)
    {
        currentStrategy = newStrategy;
        roleManager->AssignRole(currentStrategy, this->m_agents);
    }

    for(uint i=0; i<m_agents.size(); i++) {
        SSLAgent* agent = m_agents[i];
//        agent->run();
    }

}

SSLGame::~SSLGame()
{
}

SSLTeam *SSLGame::ourTeam()
{
    return world->getTeam(m_ourColor);
}

SSLTeam *SSLGame::opponentTeam()
{
    return world->getTeam(opponentColor());
}

SSLAgent *SSLGame::getAgent(unsigned int ID) const
{
    //if(this->)
    SSLAgent* agent;
    for(unsigned int i=0; i<this->m_agents.size(); ++i)
    {
        agent = m_agents.at(i);
        if((int)ID == agent->getID())
            return agent;
    }
    return NULL;
}

void SSLGame::updateAgents(bool &anyChange)
{
    vector<SSLRobot* > ours = ourTeam()->getInFieldRobots();
    for(unsigned int i=0; i<this->m_agents.size(); i++) {
        SSLAgent* agent = m_agents.at(i);
        if(ours.empty()) {
            agent->robot = NULL;
            continue;
        }
        SSLRobot* robot = ours.at(0);
        if(agent->isNull())
            anyChange = true;
        else if(agent->robot->id != robot->id)
            anyChange = true;
        if(anyChange)
            agent->robot = robot;
        ours.erase(ours.begin());
    }
}


