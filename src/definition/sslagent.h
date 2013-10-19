#ifndef SSLAGENT_H
#define SSLAGENT_H

#include "definition/SSLRobot.h"
#include "definition/SSLPost.h"
#include "soccer/roles/SSLRole.h"

class SSLAgent
{
public:
    SSLAgent();
    SSLRobot* robot;
    SSLPost* post;
    SSLRole* role;

    bool isNull();


private:
};

#endif // SSLAGENT_H
