#ifndef SSLGAME_H
#define SSLGAME_H

#include "../general.h"
#include "../../common/sslnamespace.h"
#include "SSLListener.h"
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
    SSLTeam* opponentTeam();
    std::vector<SSLAgent* > m_agents;
    SSLAgent* getAgent(unsigned int ID) const;
    SSLStrategy* currentStrategy;

    Color ourColor() const;    
    Side ourSide() const;
    Color opponentColor() const;
    Side opponentSide() const;


    Obstacle* ballObstacle;
    ObstacleSet allRobotsObstacles;
    ObstacleSet penaltyAreaObstacles;

private:
    Color m_ourColor;
    Side m_ourSide;

    void updateAgents(bool &anyChange);
    void updateObstacles();
};

#endif // SSLGAME_H
