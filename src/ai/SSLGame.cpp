#include "SSLGame.h"

#include "soccer/sslstrategymanager.h"
#include "soccer/sslrolemanager.h"

SSLGame* SSLGame::game = NULL;

SSLGame* SSLGame::getInstance(Color set_our_color, Side set_our_side)
{
    if(game == NULL)    
        game = new SSLGame(set_our_color, set_our_side);

    return game;
}

SSLGame::SSLGame(Color ourC, Side ourS)
{    
    SetColor_Side(ourC, ourS);
}

void SSLGame::SetColor_Side(Color ourC, Side ourS)
{
    _ourColor = ourC;
    _ourSide = ourS;
}

void SSLGame::check()
{
    // TODO
//    cout << "Game is running" << endl;
    strategyManager()->updateStrategy(this->currentStrategy);

    roleManager()->assignRole(this->currentStrategy, this->agents);

}

SSLGame::~SSLGame()
{
}

SSLTeam *SSLGame::ourTeam()
{
    return world()->team[_ourColor];
}

SSLAgent *SSLGame::getAgent(unsigned int ID) const
{
    //if(this->)
    SSLAgent* agent;
    for(unsigned int i=0; i<this->agents.size(); ++i)
    {
        agent = agents.at(i);
        if(ID == agent->getID())
            return agent;
    }
    return NULL;
}

Color SSLGame::ourColor() const
{
    return _ourColor;
}

Side SSLGame::ourSide() const
{
    return _ourSide;
}

Color SSLGame::enemyColor() const
{
    return (_ourColor==Yellow)? Blue:Yellow;
}

Side SSLGame::enemySide() const
{
    return (_ourSide==Left)? Right:Left;
}

SSLWorldModel *SSLGame::world()
{
    return SSLWorldModel::getInstance();
}

SSLStrategyManager *SSLGame::strategyManager()
{
    return SSLStrategyManager::getInstance();
}

SSLRoleManager *SSLGame::roleManager()
{
    return SSLRoleManager::getInstance();
}
