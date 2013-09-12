//#include <QCoreApplication>
#include <QApplication>
#include <QDebug>
#include <iostream>

using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    cerr << "Program is running ... ";
    
    return a.exec();
}

