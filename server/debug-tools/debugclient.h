#ifndef DEBUGCLIENT_H
#define DEBUGCLIENT_H

#include <string>
#include "vector2d.h"
#include "../../shared/proto/plotter/cpp/message_plotter.pb.h"
#include "robotstate.h"

class Debugger
{
    static Debugger* empty_instance;
public:    
    static Debugger* instance;

    static Debugger* dbg() {
        if(instance == NULL) {
            if(!empty_instance) {
                empty_instance = new Debugger;
            }
            return empty_instance;
        }
        return instance;
    }

    virtual void print(const char* msg, double time, std::string category = "general") {}
    virtual void print(const char *msg, std::string category = "general") {}

    virtual void plot(double value, const char* name = "", const char* category = "general") {}
    virtual void plot(std::vector<double> values,
                      std::vector<const char*> names,
                      const char* category = "general") {}
    virtual void plot(Plotter_Packet packet) {}
    virtual void plot(double value, double key, std::string name = "", std::string category = "general") {}

    virtual void updateWorldModel(RobotState &rs)  {}
    virtual void updateWorldModel(BallState &bs) {}

    virtual void scatter(double x, double y, std::string name = "", std::string category = "general") {}
    virtual void scatter(const Vector2D& data, std::string name = "", std::string category = "general") {}

    virtual void drawCircle() {}
    virtual void drawLine() {}
    virtual void drawRect() {}

    Debugger() {}
protected:
//    void sendWorldModelPacket();

};


#endif // DEBUGCLIENT_H
