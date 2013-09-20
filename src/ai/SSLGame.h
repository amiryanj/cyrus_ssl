#ifndef SSLGAME_H
#define SSLGAME_H

#include "../general.h"
#include "../ai/SSLWorldModel.h"

class SSLGame
{
public:
    static SSLGame* getInstance();
    SSLWorldModel *world;
    void run();

private:
    SSLGame();
    ~SSLGame();
    static SSLGame* game;

    Color ourColor;
    inline Color enemyColor();
    Side ourSide;
    inline Side enemySide();

};

#endif // SSLGAME_H
