#ifndef _SSLAGENT_H
#define _SSLAGENT_H

#include "../definition/SSLRobot.h"
#include "../general.h"

class SSLRole;
class SSLSkill;

class SSLAgent
{
    friend class GUIHandler;
    friend class SSLSkill;
public:
    SSLAgent();
    ~SSLAgent();

    SSLRobot* robot;
    SSLRole*  role;
    SSLSkill* skill;

    bool isNull();
    int getID() const;

    void run();

private:
};

#endif // _SSLAGENT_H
