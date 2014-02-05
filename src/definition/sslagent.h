#ifndef SSLAGENT_H
#define SSLAGENT_H

#include "definition/SSLRobot.h"
#include "soccer/roles/SSLRole.h"
#include "general.h"
#include "../planning/rrtplanner.h"

class SSLAgent
{
public:
    SSLAgent();
    ~SSLAgent();

    SSLRobot* realRobot;
    SSLRole* role;

    Planner::State* target;

    bool isNull();
    int getID() const;

    void run();


private:
};

#endif // SSLAGENT_H
