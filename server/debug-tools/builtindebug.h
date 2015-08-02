#ifndef BUILTINDEBUG_H
#define BUILTINDEBUG_H

#include "debugclient.h"
#include "plot-manager/plotmanagerwidget.h"
#include <QObject>

class BuiltInDebug : public QObject , public Debugger
{
    Q_OBJECT
public:
    BuiltInDebug();
    ~BuiltInDebug() {}

    void print(const char* msg, double time, std::string category = "general");
    void print(const char *msg, std::string category = "general");

    void plot(double value, const char* name = "", const char* category = "general");
    void plot(double value, double key, std::string name = "", std::string category = "general");

    void drawCircle();
    void drawLine();
    void drawRect();


signals:
    void plotSignal(double value, const char* name, const char* category);


protected:


};

#endif // BUILTINDEBUG_H
