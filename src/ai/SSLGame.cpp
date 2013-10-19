#include "SSLGame.h"

#include "soccer/sslstrategymanager.h"
#include "soccer/SSLPostManager.h"
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
    world = SSLWorldModel::getInstance();
    postManager = SSLPostManager::getInstance();
    strategyManager = SSLStrategyManager::getInstance();
    roleManager = SSLRoleManager::getInstance();

    ourTeam = (world->team[0]->color == ourColor())? world->team[0]:world->team[1];
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
    strategyManager->updateStrategy(this->currentStrategy);
    postManager->assignPost(this->currentStrategy, this->agents);

//    roleManager->assignRole(this->agents);


}

SSLGame::~SSLGame()
{
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
