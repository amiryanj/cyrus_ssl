#ifndef SSLGAME_H
#define SSLGAME_H

#include "../general.h"
#include "../tools/SSLListener.h"
#include "../planner/planning/planningproblem.h"

class SSLStrategyManager;
class SSLRoleManager;
class SSLStrategy;
class SSLAgent;
class SSLTeam;

#define decision SSLGame::getInstance()
#define game SSLGame::getInstance()

using namespace SSL;

class SSLGame : SSLListener
{
    static SSLGame* game_instance;
    SSLGame(Color ourC, Side ourS);

public:
    static SSLGame* getInstance(Color set_our_color, Side set_our_side);
    static SSLGame* getInstance();
    void SetColor_Side(Color ourC, Side ourS);
    void check();
    ~SSLGame();

    SSLTeam* ourTeam();
    std::vector<SSLAgent* > m_agents;
    SSLAgent* getAgent(unsigned int ID) const;
    SSLStrategy* currentStrategy;

    bool hasAgent();
    Color ourColor() const;    
    Side ourSide() const;
    Color opponentColor() const;
    Side opponentSide() const;

    ObstacleSet allRobotsObs;
    Obstacle* ballOb;
    ObstacleSet penaltyAreaObs;

private:
    Color m_ourColor;
    Side m_ourSide;

    ObstacleSet myDynamicObstacleSet;

    void updateAgents(bool &anyChange);
    void updateObstacles();
};

#endif // SSLGAME_H
