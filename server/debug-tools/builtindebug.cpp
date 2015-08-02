#include "builtindebug.h"
#include "mainwindow.h"
#include <iostream>

using namespace std;

BuiltInDebug::BuiltInDebug() : QObject()
{
    connect(this, SIGNAL(plotSignal(double,const char*,const char*)),
            MainWindow::getInstance()->PMW, SLOT(plot(double,const char*,const char*)));
}

void BuiltInDebug::print(const char *msg, double time, std::string category)
{
    cout << "[" << category << "] " << "(" << time << "): " << msg << endl;
}

void BuiltInDebug::print(const char *msg, std::string category)
{
    cout << "[" << category << "]:" << msg << endl;
}

void BuiltInDebug::plot(double value, const char *name, const char *category)
{
    emit plotSignal(value, name, category);
//    MainWindow::getInstance()->PMW->plot(value, name, category);
//    Plotter_Packet pp;
//    pp.add_values(value);
//    pp.add_legends(name);
//    pp.set_name(category);
//    MainWindow::getInstance()->PMW->newPlotMessage(pp);
}

void BuiltInDebug::plot(double value, double key, std::string name, std::string category)
{
}

void BuiltInDebug::drawCircle()
{
}

void BuiltInDebug::drawLine()
{
}

void BuiltInDebug::drawRect()
{
}
