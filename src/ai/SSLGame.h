#ifndef SSLGAME_H
#define SSLGAME_H

#include "../general.h"
#include "SSLWorldModel.h"
#include "definition/sslagent.h"
#include "tools/SSLListener.h"
#include "definition/sslstrategy.h"

class SSLStrategyManager;
class SSLRoleManager;

class SSLGame : SSLListener
{
    static SSLGame* game;
    SSLGame(Color ourC, Side ourS);

public:
    static SSLGame* getInstance(Color set_our_color = OUR_COLOR, Side set_our_side = OUR_SIDE);
    void SetColor_Side(Color ourC, Side ourS);
    void check();
    ~SSLGame();

    SSLTeam* ourTeam();
    std::vector<SSLAgent*> agents;
    SSLAgent* getAgent(unsigned int ID) const;
    SSLStrategy currentStrategy;

    bool hasAgent();
    Color ourColor() const;
    Side ourSide() const;
    inline Color enemyColor() const;
    inline Side enemySide() const;

private:
    Color _ourColor;
    Side _ourSide;

    SSLWorldModel *world();
    SSLStrategyManager *strategyManager();
    SSLRoleManager *roleManager();

};

#endif // SSLGAME_H
