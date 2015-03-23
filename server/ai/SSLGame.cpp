#include "SSLGame.h"

#include "SSLWorldModel.h"
#include "../soccer/sslstrategymanager.h"
#include "../definition/sslstrategy.h"
#include "../definition/sslagent.h"
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


    // initializing field obstacles for agent
    // ****************************************************************************************
    penaltyAreaObs.reserve(5);
    int z = (int) ourSide();
    Obstacle* myPenaltyArea_C = new Obstacle(Obstacle::Field, b2Vec2(z* FIELD_LENGTH/2, 0),
                                                    FIELD_PENALTY_AREA_RADIUS * 0.9, 0);
    Obstacle* myPenaltyArea_T = new Obstacle(Obstacle::Field, b2Vec2(z* FIELD_LENGTH/2, FIELD_PENALTY_AREA_WIDTH/2),
                                                    FIELD_PENALTY_AREA_RADIUS * 0.9, 0);
    Obstacle* myPenaltyArea_D = new Obstacle(Obstacle::Field, b2Vec2(z* FIELD_LENGTH/2, -FIELD_PENALTY_AREA_WIDTH/2),
                                                    FIELD_PENALTY_AREA_RADIUS * 0.9, 0);
//    Obstacle* myPenaltyArea_C = new Obstacle(b2Vec2(z* FIELD_LENGTH/2, 0),
//                                                    FIELD_PENALTY_AREA_RADIUS*2 * .9, FIELD_PENALTY_AREA_WIDTH, 0);
    Obstacle* outFieldArea_R = new Obstacle(Obstacle::Field, b2Vec2(FIELD_LENGTH/2 + 300, 0),
                                                                    150*2 ,  FIELD_WIDTH, 0);
    Obstacle* outFieldArea_L = new Obstacle(Obstacle::Field, b2Vec2(-FIELD_LENGTH/2 - 300, 0),
                                                                    150*2 ,  FIELD_WIDTH, 0);
    penaltyAreaObs.push_back(myPenaltyArea_C);
    penaltyAreaObs.push_back(myPenaltyArea_T);
    penaltyAreaObs.push_back(myPenaltyArea_D);

    penaltyAreaObs.push_back(outFieldArea_L);
    penaltyAreaObs.push_back(outFieldArea_R);

    allRobotsObs.reserve(MAX_ID_NUM * 2);
    for(unsigned int i=0; i< MAX_ID_NUM *2; i++) {
        Obstacle* ob_ = new Obstacle(Obstacle::Robot, b2Vec2(0, 0), ROBOT_RADIUS, 0);
        allRobotsObs.push_back(ob_);
    }

    ballOb = new Obstacle(Obstacle::Ball, b2Vec2(0,0), BALL_RADIUS, 0);
    // ****************************************************************************************

}

void SSLGame::SetColor_Side(Color ourC, Side ourS)
{
    m_ourColor = ourC;
    m_ourSide = ourS;
}

void SSLGame::check()
{
    // TODO
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

    updateObstacles();

    for(uint i=0; i<m_agents.size(); i++) {
        SSLAgent* agent = m_agents[i];
        agent->run();
    }

}

SSLGame::~SSLGame()
{
}

SSLTeam *SSLGame::ourTeam()
{
    return world->team[m_ourColor];
}

SSLTeam *SSLGame::opponentTeam()
{
    return world->team[(int)opponentColor()];
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

Color SSLGame::ourColor() const
{
    return m_ourColor;
}

Side SSLGame::ourSide() const
{
    return m_ourSide;
}

Color SSLGame::opponentColor() const
{
    return (m_ourColor==Yellow)? Blue:Yellow;
}

Side SSLGame::opponentSide() const
{
    return (m_ourSide==Left)? Right:Left;
}

void SSLGame::updateAgents(bool &anyChange)
{
    vector<SSLRobot* > ours = ourTeam()->inFields();
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

void SSLGame::updateObstacles()
{
    // it is done in SSLSkill for each robot individually
//    vector<SSLRobot* > all_actual_robots = world->allRobots();
//    for(unsigned int i=0; i < allRobotsObs.size(); i++)
//    {
//        Obstacle* ob_  = allRobotsObs.at(i);
//        SSLRobot* rob_ = all_actual_robots.at(i);
//        if(rob_->isInField) {
//            ob_->m_transform.Set(Vector2D(rob_->Position().X(), rob_->Position().Y()).b2vec2(), rob_->Position().Teta());
//        }
//        else {
//            ob_->m_transform.Set(Vector2D(INFINITY, INFINITY).b2vec2(), 0);
//        }
//    }

    SSLBall* actual_ball = world->mainBall();
    ballOb->m_transform.Set(b2Vec2(actual_ball->Position().X(), actual_ball->Position().Y()), 0);
}
