//#include <QCoreApplication>
#include <QApplication>
#include <QDebug>
#include <iostream>
#include "ai/SSLGame.h"

using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    cerr << "Main is running ... " << "\n";
    SSLGame::game->run();
    
    return a.exec();
}

