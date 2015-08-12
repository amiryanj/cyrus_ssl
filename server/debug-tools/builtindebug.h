#ifndef BUILTINDEBUG_H
#define BUILTINDEBUG_H

#include "debugclient.h"
#include <vector>
#include <QVector>
#include <QObject>
#include <QString>

class BuiltInDebug : public QObject , public Debugger
{
    Q_OBJECT
public:
    BuiltInDebug();
    ~BuiltInDebug() {}

    void print(const char* msg, double time, std::string category = "general");
    void print(const char *msg, std::string category = "general");

    void plot(double value, const char* name = "", const char* category = "general");
    void plot(std::vector<double> values, std::vector<const char*> names, const char* category = "general");
    void plot(Plotter_Packet packet);
    void plot(double value, double key, std::string name = "", std::string category = "general");

    void updateWorldModel(RobotState &rs);

    void drawCircle();
    void drawLine();
    void drawRect();


signals:
    void plotSignal(double value, QString name, QString category);
    void plotPacketSignal(Plotter_Packet p);
    void updateRobotStateSignal(RobotState rs);
    void newMessageSignal(const char *msg , QString category);
//    void plotSignal(QVector<double> values, QStringList names, QString category);


protected:
    Plotter_Packet under_use_plotter_packet;


};

#endif // BUILTINDEBUG_H
