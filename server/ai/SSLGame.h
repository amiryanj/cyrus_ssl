#ifndef _SSLGAME_H
#define _SSLGAME_H

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

    inline Color ourColor() const;
    inline Side ourSide() const;
    inline Color opponentColor() const;
    inline Side opponentSide() const;

    unsigned long game_running_counter;

private:
    Color m_ourColor;
    Side m_ourSide;

    void updateAgents(bool &anyChange);
};


inline Color SSLGame::ourColor() const
{
    return m_ourColor;
}

inline Side SSLGame::ourSide() const
{
    return m_ourSide;
}

inline Color SSLGame::opponentColor() const
{
    return (m_ourColor==Yellow)? Blue:Yellow;
}

inline Side SSLGame::opponentSide() const
{
    return (m_ourSide==Left)? Right:Left;
}

#endif // SSLGAME_H
