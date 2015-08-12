#include "builtindebug.h"
#include "mainwindow.h"
#include <iostream>
#include "plot-manager/plotmanagerwidget.h"

using namespace std;

BuiltInDebug::BuiltInDebug() : QObject()
{
    connect(this, SIGNAL(plotSignal(double,QString,QString)),
            MainWindow::getInstance()->PMW, SLOT(plot(double,QString,QString)));

    connect(this, SIGNAL(plotPacketSignal(Plotter_Packet)),
            MainWindow::getInstance()->PMW, SLOT(newPlotMessage(Plotter_Packet)));

    connect(this, SIGNAL(updateRobotStateSignal(RobotState)),
            MainWindow::getInstance()->watchField, SLOT(updateRobotState(RobotState)));

    connect(this , SIGNAL(newMessageSignal(const char*,QString)),
            MainWindow::getInstance()->MSG,SLOT(newMessage(const char*,QString)));

    connect(this, SIGNAL(updateBallStateSignal(BallState)),
            MainWindow::getInstance()->watchField, SLOT(updateBallState(BallState)));


    qRegisterMetaType<RobotState>("RobotState");
    qRegisterMetaType<BallState>("BallState");

}

void BuiltInDebug::print(const char *msg, double time, std::string category)
{
    cout << "[" << category << "] " << "(" << time << "): " << msg << endl;
}

void BuiltInDebug::print(const char *msg, std::string category)
{
   // cout << "[" << category << "]:" << msg << endl;

    emit newMessageSignal(msg,QString::fromStdString(category));
}

void BuiltInDebug::plot(double value, const char *name, const char *category)
{
    emit plotSignal(value, QString(name), QString(category));
//    MainWindow::getInstance()->PMW->plot(value, name, category);
//    Plotter_Packet pp;
//    pp.add_values(value);
//    pp.add_legends(name);
//    pp.set_name(category);
    //    MainWindow::getInstance()->PMW->newPlotMessage(pp);
}

void BuiltInDebug::plot(Plotter_Packet packet)
{
//    under_use_plotter_packet.CopyFrom(packet);
//    emit plotPacketSignal(under_use_plotter_packet);
    emit plotPacketSignal(packet);
}

void BuiltInDebug::plot(vector<double> values, vector<const char*> names, const char *category)
{
//    QVector<double> values_qvec;
//    values_qvec.insert(values.begin(), values.size(), );
//    emit plotSignal(values_qvec, );
}

void BuiltInDebug::plot(double value, double key, std::string name, std::string category)
{
}

void BuiltInDebug::updateWorldModel(RobotState &rs)
{
    emit updateRobotStateSignal(rs);
}

void BuiltInDebug::updateWorldModel(BallState &bs)
{
    emit updateBallStateSignal(bs);
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
