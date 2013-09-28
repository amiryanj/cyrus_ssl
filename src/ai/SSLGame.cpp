#include "SSLGame.h"

SSLGame* SSLGame::game = NULL;

SSLGame* SSLGame::getInstance()
{
    if(game == NULL)
        game = new SSLGame();
    return game;
}


SSLGame::SSLGame()
{
    world = SSLWorldModel::getInstace();

}

Color SSLGame::enemyColor()
{
    return (ourColor==Yellow)? Blue:Yellow;
}

Side SSLGame::enemySide()
{
    return (ourSide==Left)? Right:Left;
}


void SSLGame::run()
{
    cerr << "Game is running" ;

}
