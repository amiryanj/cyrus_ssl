#ifndef SSLAGENT_H
#define SSLAGENT_H

#include "definition/SSLRobot.h"
#include "soccer/roles/SSLRole.h"
#include "general.h"

class SSLAgent
{
public:
    SSLAgent();
    SSLRobot* robot;
    SSLRole* role;

    bool isNull();
    int getID() const;

    void run();


private:
};

#endif // SSLAGENT_H
